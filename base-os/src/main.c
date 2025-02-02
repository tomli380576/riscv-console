#include <stdint.h>
#include "RVCOS.h"

#define CART_STAT_REG (*(volatile uint32_t *)0x4000001C) // addr is the num, cast to pointer, then deref
#define TIME_REG (*(volatile uint32_t *)0x40000008)

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t *saved_sp;
volatile uint32_t *MainThread, *OtherThread;

typedef uint32_t (*TEntry)(uint32_t param);
typedef void (*TFunctionPointer)(void);

// Assembly functions
void enter_cartridge(void);

int main() {
  saved_sp = &controller_status;
  int last_global = 42;

  int x_pos = 12;
  int param = 20;

  while (1) {
    if (CART_STAT_REG & 0x1) {
      enter_cartridge();
      writeString("back to OS\n");
      while (CART_STAT_REG & 0x1); // wait for the cartridge to be removed
    }
  }
  return 0;
}

/**
 * @brief
 *
 * @param p1 param1
 * @param p2 param2
 * @param p3 ...
 * @param p4
 * @param p5
 * @param syscall_code .. switch case on this to call the corresponding functions
 * @return uint32_t
 */
void c_syscall_handler(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5,
                       uint32_t syscall_code) {
  switch (syscall_code) {
    case 0: {
      RVCInitialize(p1);
      break;
    }
    case 1: {
      RVCThreadCreate(p1, p2, p3, p4, p5);
      break;
    }
    case 2: {
      RVCThreadDelete(p1);
      break;
    }
    case 3: {
      RVCThreadActivate(p1);
      break;
    }
    case 4: {
      RVCThreadTerminate(p1, p2);
      break;
    }
    case 5: {
      RVCThreadWait(p1, p2, p3);
      break;
    }
    case 6: {
      RVCThreadID(p1);
      break;
    }
    case 7: {
      RVCThreadState(p1, p2);
      break;
    }
    case 8: {
      RVCThreadSleep(p1);
      break;
    }
    case 9: {
      RVCTickMS(p1);
      break;
    }
    case 10: {
      RVCTickCount(p1);
      break;
    }
    case 11: {
      RVCWriteText(p1, p2);
      break;
    }
    case 12: {
      RVCReadController(p1);
      break;
    }
    case 13: {
      RVCMemoryPoolCreate(p1, p2, p3);
      break;
    }
    case 14: {
      RVCMemoryPoolDelete(p1);
      break;
    }
    case 15: {
      RVCMemoryPoolQuery(p1, p2);
      break;
    }
    case 16: {
      RVCMemoryPoolAllocate(p1, p2, p3);
      break;
    }
    case 17: {
      RVCMemoryPoolDeallocate(p1, p2);
      break;
    }
    case 18: {
      RVCMutexCreate(p1);
      break;
    }
    case 19: {
      RVCMutexDelete(p1);
      break;
    }
    case 20: {
      RVCMutexQuery(p1, p2);
      break;
    }
    case 21: {
      RVCMutexAcquire(p1, p2);
      break;
    }
    case 22: {
      RVCMutexRelease(p1);
      break;
    }
    case 23: {
      RVCChangeVideoMode(p1);
      break;
    }
      // case 24:{
      //   RVCSetVideoUpcall(p1, p2);
      //   break;
      // }
      // case 25:{
      //   RVCGraphicCreate(p1, p2);
      //   break;
      // }
      // case 26:{
      //   RVCGraphicDelete(p1);
      //   break;
      // }
      // case 27:{
      //   RVCGraphicActivate(p1, p2, p3, p4);
      //   break;
      // }
      // case 28:{
      //   RVCGraphicActivate(p1, p2, p3, p4);
      //   break;
      // }
      // case 29:{
      //   RVCGraphicDeactivate(p1);
      //   break;
      // }
      // case 30:{
      //   RVCGraphicDraw(p1, p2, p3, p4, p5);
      //   break;
      // }
      // case 31:{
      //   RVCPaletteCreate(p1);
      //   break;
      // }
      // case 32:{
      //   RVCPaletteDelete(p1);
      //   break;
      // }
      // case 33:{
      //   RVCPaletteUpdate(p1, p2, p3, p4);
      //   break;
      // }

    default:
      break;
  }
}
