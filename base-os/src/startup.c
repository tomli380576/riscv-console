#include <stdint.h>
#include <stdlib.h>

#include "RVCOS.h"

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// Adapted from
// https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void) {
  uint32_t result;
  asm volatile("csrr %0, mstatus" : "=r"(result));
  return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val) {
  asm volatile("csrw mstatus, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val) {
  asm volatile("csrw mie, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_enable_interrupts(void) {
  asm volatile("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_disable_interrupts(void) {
  asm volatile("csrci mstatus, 0x8");
}

#define MTIME_LOW (*((volatile uint32_t *)0x40000008))  // Machine Time
#define MTIME_HIGH (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH (*((volatile uint32_t *)0x40000014))
#define CONTROLLER (*((volatile uint32_t *)0x40000018))

void init(void) {
  uint8_t *Source = _erodata;
  uint8_t *Base = _data < _sdata ? _data : _sdata;
  uint8_t *End = _edata > _esdata ? _edata : _esdata;

  while (Base < End) {
    *Base++ = *Source++;
  }
  Base = _bss;
  End = _ebss;
  while (Base < End) {
    *Base++ = 0;
  }

  csr_write_mie(0x888);     // Enable all interrupt soruces
  csr_enable_interrupts();  // Global interrupt enable
  MTIMECMP_LOW = 1;
  MTIMECMP_HIGH = 0;
}

extern volatile int global;
extern volatile uint32_t controller_status;

// Need to save MEPC and global pointer before calling this! In interrupts.s
// TODO: Add Parameters if needed, param values are in a0, a1, ...
void c_interrupt_handler(int p1, int p2, int p3, int p4, int p5) {
  // * this is called every 2 ms, use this to call the scheduler
  // WriteString("int handler\n");

  // writeInt(p5);
  // writeString("\n");
  uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH) << 32) | MTIMECMP_LOW;
  NewCompare += 100;
  MTIMECMP_HIGH = NewCompare >> 32;
  MTIMECMP_LOW = NewCompare;
  global++;  // why ++???
  controller_status = CONTROLLER;

  csr_disable_interrupts();

  if (getPQReady()){
    //schedule();
  }

  //writeString("scheduler finished\n");
  
  csr_enable_interrupts();
}

void *_sbrk(int incr) {
  extern char _heapbase; /* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &_heapbase;
  }
  prev_heap_end = heap_end;
  heap_end += incr;

  return (void *)prev_heap_end;
}