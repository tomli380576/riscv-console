#ifndef RVCOS_H
#define RVCOS_H

#include <stdint.h>
#include <stdlib.h>

#define RVCOS_STATUS_FAILURE ((TStatus)0x00)
#define RVCOS_STATUS_SUCCESS ((TStatus)0x01)
#define RVCOS_STATUS_ERROR_INVALID_PARAMETER ((TStatus)0x02)
#define RVCOS_STATUS_ERROR_INVALID_ID ((TStatus)0x03)
#define RVCOS_STATUS_ERROR_INVALID_STATE ((TStatus)0x04)
#define RVCOS_STATUS_ERROR_INSUFFICIENT_RESOURCES ((TStatus)0x05)

#define MAIN_THREAD_ID ((uint32_t)0x01)
#define IDLE_THREAD_ID ((uint32_t)0x00)

#define RVCOS_THREAD_STATE_CREATED ((TThreadState)0x01)
#define RVCOS_THREAD_STATE_DEAD ((TThreadState)0x02)
#define RVCOS_THREAD_STATE_RUNNING ((TThreadState)0x03)
#define RVCOS_THREAD_STATE_READY ((TThreadState)0x04)
#define RVCOS_THREAD_STATE_WAITING ((TThreadState)0x05)
#define RVCOS_THREAD_STATE_SLEEP ((TThreadSTate)0x06)

#define RVCOS_THREAD_PRIORITY_IDLE ((TThreadPriority)0x00)
#define RVCOS_THREAD_PRIORITY_LOW ((TThreadPriority)0x01)
#define RVCOS_THREAD_PRIORITY_NORMAL ((TThreadPriority)0x02)
#define RVCOS_THREAD_PRIORITY_HIGH ((TThreadPriority)0x03)

#define RVCOS_THREAD_ID_INVALID ((TThreadID)-1)

#define RVCOS_TIMEOUT_INFINITE ((TTick)0)
#define RVCOS_TIMEOUT_IMMEDIATE ((TTick)-1)

#define RVCOS_MEMORY_POOL_ID_SYSTEM ((TMemoryPoolID)0)
#define RVCOS_MEMORY_POOL_ID_INVALID ((TMemoryPoolID)-1)

#define RVCMemoryAllocate(size, pointer) RVCMemoryPoolAllocate(RVCOS_MEMORY_POOL_ID_SYSTEM, (size), (pointer))
#define RVCMemoryDeallocate(pointer) RVCMemoryPoolDeallocate(RVCOS_MEMORY_POOL_ID_SYSTEM, (pointer))

#define RVCOS_MUTEX_ID_INVALID ((TMutexID)-1)
#define RVCOS_MUTEX_STATE_LOCKED ((TMutexState)0x00)
#define RVCOS_MUTEX_STATE_UNLOCKED ((TMutexState)0x01)

#define RVCOS_VIDEO_MODE_TEXT      ((TVideoMode)0) 
#define RVCOS_VIDEO_MODE_GRAPHICS  ((TVideoMode)1) 

#define RVCOS_GRAPHIC_ID_INVALID                    ((TGraphicID)-1)

#define RVCOS_GRAPHIC_TYPE_FULL                     ((TGraphicType)0)
#define RVCOS_GRAPHIC_TYPE_LARGE                    ((TGraphicType)1)
#define RVCOS_GRAPHIC_TYPE_SMALL                    ((TGraphicType)2)

#define RVCOS_PALETTE_ID_DEFAULT                    ((TPaletteID)0)
#define RVCOS_PALETTE_ID_INVALID                    ((TPaletteID)-1)

#define TIME_REG (*(volatile uint32_t *)0x40000008)           // already derefed, ready to use as value
#define CONTROLLER_REG_VAL (*(volatile uint32_t *)0x40000018) // already derefed
#define MAX_VRAM_INDEX (36 * 64 - 1)
#define MIN_ALLOC_SIZE 0x40

typedef uint32_t TStatus, * TStatusRef;
typedef uint32_t TTick, * TTickRef;
typedef int32_t TThreadReturn, * TThreadReturnRef;
typedef uint32_t TMemorySize, * TMemorySizeRef;
typedef uint32_t TThreadID, * TThreadIDRef;
typedef uint32_t TThreadPriority, * TThreadPriorityRef;
typedef uint32_t TThreadState, * TThreadStateRef;
typedef char TTextCharacter, * TTextCharacterRef;
typedef uint32_t TMemoryPoolID, * TMemoryPoolIDRef;
typedef uint32_t TMutexID, * TMutexIDRef, TMutexOwner, TMutexState; // State: 1 = unlocked, 0 = locked
typedef uint32_t TVideoMode, *TVideoModeRef;
typedef uint32_t TGraphicID, *TGraphicIDRef;
typedef uint32_t TGraphicType, *TGraphicTypeRef;
typedef uint32_t TPaletteID, *TPaletteIDRef;
typedef uint8_t TPaletteIndex, *TPaletteIndexRef;

typedef uint32_t(*TEntry)(uint32_t param);

typedef TThreadReturn(*TThreadEntry)(void*);

typedef void (*TFunctionPointer)(void);
typedef void (*TUpcallPointer)(void *param);

typedef struct
{
    uint32_t DLeft : 1; // num after colon means how many bits this field has
    uint32_t DUp : 1;
    uint32_t DDown : 1;
    uint32_t DRight : 1;
    uint32_t DButton1 : 1;
    uint32_t DButton2 : 1;
    uint32_t DButton3 : 1;
    uint32_t DButton4 : 1;   // 1 bit field
    uint32_t DReserved : 24; // 24 bit field
} SControllerStatus, * SControllerStatusRef;

typedef struct{
    int32_t DXPosition;
    int32_t DYPosition;
    uint32_t DZPosition;
} SGraphicPosition, *SGraphicPositionRef;

typedef struct{
    uint32_t DWidth;
    uint32_t DHeight;
} SGraphicDimensions, *SGraphicDimensionsRef;

typedef struct{
    uint32_t DBlue : 8;
    uint32_t DGreen : 8;
    uint32_t DRed : 8;
    uint32_t DAlpha : 8;
} SColor, *SColorRef;

typedef struct {
    uint32_t DPalette : 2;
    uint32_t DXOffset : 10;
    uint32_t DYOffset : 9;
    uint32_t DWidth : 5;
    uint32_t DHeight : 5;
    uint32_t DReserved : 1;
} SLargeSpriteControl, *SLargeSpriteControlRef;

typedef struct {
    uint32_t DPalette : 2;
    uint32_t DXOffset : 10;
    uint32_t DYOffset : 9;
    uint32_t DWidth : 4;
    uint32_t DHeight : 4;
    uint32_t DZ : 3;
} SSmallSpriteControl, * SSmallSpriteControlRef;
typedef struct {
    uint32_t DPalette : 2;
    uint32_t DXOffset : 10;
    uint32_t DYOffset : 10;
    uint32_t DZ : 3;
    uint32_t DReserved : 7;
} SBackgroundControl, *SBackgroundControlRef;

typedef struct {
    uint32_t DMode : 1;
    uint32_t DRefresh : 7;
    uint32_t DReserved : 24;
} SVideoControllerMode, *SVideoControllerModeRef;

TStatus RVCInitialize(uint32_t* gp);

TStatus RVCTickMS(uint32_t* tickmsref);
TStatus RVCTickCount(TTickRef tickref);

TStatus RVCThreadCreate(TThreadEntry entry, void* param, TMemorySize memsize, TThreadPriority prio, TThreadIDRef tid);
TStatus RVCThreadDelete(TThreadID thread);
TStatus RVCThreadActivate(TThreadID thread);
TStatus RVCThreadTerminate(TThreadID thread, TThreadReturn returnval);
TStatus RVCThreadWait(TThreadID thread, TThreadReturnRef returnref, TTick timeout);
TStatus RVCThreadID(TThreadIDRef threadref);
TStatus RVCThreadState(TThreadID thread, TThreadStateRef stateref);
TStatus RVCThreadSleep(TTick tick);

#define RVCMemoryAllocate(size, pointer) RVCMemoryPoolAllocate(RVCOS_MEMORY_POOL_ID_SYSTEM, (size), (pointer))
#define RVCMemoryDeallocate(pointer) RVCMemoryPoolDeallocate(RVCOS_MEMORY_POOL_ID_SYSTEM, (pointer))

TStatus RVCMemoryPoolCreate(void* base, TMemorySize size, TMemoryPoolIDRef memoryref);
TStatus RVCMemoryPoolDelete(TMemoryPoolID memory);
TStatus RVCMemoryPoolQuery(TMemoryPoolID memory, TMemorySizeRef bytesleft);
TStatus RVCMemoryPoolAllocate(TMemoryPoolID memory, TMemorySize size, void** pointer);
TStatus RVCMemoryPoolDeallocate(TMemoryPoolID memory, void* pointer);

TStatus RVCMutexCreate(TMutexIDRef mutexref);
TStatus RVCMutexDelete(TMutexID mutex);
TStatus RVCMutexQuery(TMutexID mutex, TThreadIDRef ownerref);
TStatus RVCMutexAcquire(TMutexID mutex, TTick timeout);
TStatus RVCMutexRelease(TMutexID mutex);

TStatus RVCWriteText(const TTextCharacter* buffer, TMemorySize writesize);
TStatus RVCReadController(SControllerStatusRef statusref);

TStatus RVCChangeVideoMode(TVideoMode mode);
TStatus RVCSetVideoUpcall(TThreadEntry upcall, void *param);

TStatus RVCGraphicCreate(TGraphicType type, TGraphicIDRef gidref);
TStatus RVCGraphicDelete(TGraphicID gid);
TStatus RVCGraphicActivate(TGraphicID gid, SGraphicPositionRef pos, SGraphicDimensionsRef dim, TPaletteID pid);
TStatus RVCGraphicDeactivate(TGraphicID gid);
TStatus RVCGraphicDraw(TGraphicID gid, SGraphicPositionRef pos, SGraphicDimensionsRef dim, TPaletteIndexRef src, uint32_t srcwidth);

TStatus RVCPaletteCreate(TPaletteIDRef pidref);
TStatus RVCPaletteDelete(TPaletteID pid);
TStatus RVCPaletteUpdate(TPaletteID pid, SColorRef cols, TPaletteIndex offset, uint32_t count);

/**
 * Helper functions
 */
void writeString(const char* str);
void writeInt(uint32_t val);
void idleFunction();
void threadSkeleton();
void schedule();
uint32_t getPQReady();

typedef struct
{
    TThreadID thread_id;
    TThreadState state;
    TThreadPriority priority;
    TThreadEntry entry;
    TThreadReturn ret_val;
    uint32_t mem_size;

    void* param;
    void* sp;

    struct MUTEX* held_mutexes; // this is probably wrong. need a list of held mutexes idk syntax for that

    uint32_t sleep_tick; // decrement this if not null and state is sleeping
} TCB;

typedef struct
{
    TMutexID mutex_id;
    TMutexIDRef mutex_ref;
    TMutexOwner owner;
    TMutexState state;
} MUTEX;

typedef struct _MemoryChunk
{
    TMemorySize data_size; // in bytes
    uint32_t isFree;
    struct _MemoryChunk* next;
    struct _MemoryChunk* prev;
} MemoryChunk;

typedef struct
{
    MemoryChunk* first_chunk;
    TMemoryPoolID pool_id;
    TMemorySize pool_size;
    TMemorySize bytes_left;
} MemoryPoolController;

#endif