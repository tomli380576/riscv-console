#ifndef RVCOS_H
#define RVCOS_H

#include <stdint.h>

#define RVCOS_STATUS_FAILURE                        ((TStatus)0x00)
#define RVCOS_STATUS_SUCCESS                        ((TStatus)0x01)
#define RVCOS_STATUS_ERROR_INVALID_PARAMETER        ((TStatus)0x02)
#define RVCOS_STATUS_ERROR_INVALID_ID               ((TStatus)0x03)
#define RVCOS_STATUS_ERROR_INVALID_STATE            ((TStatus)0x04)
#define RVCOS_STATUS_ERROR_INSUFFICIENT_RESOURCES   ((TStatus)0x05)

#define RVCOS_THREAD_STATE_CREATED                  ((TThreadState)0x01)
#define RVCOS_THREAD_STATE_DEAD                     ((TThreadState)0x02)
#define RVCOS_THREAD_STATE_RUNNING                  ((TThreadState)0x03)
#define RVCOS_THREAD_STATE_READY                    ((TThreadState)0x04)
#define RVCOS_THREAD_STATE_WAITING                  ((TThreadState)0x05)

#define RVCOS_THREAD_PRIORITY_LOW                   ((TThreadPriority)0x01)
#define RVCOS_THREAD_PRIORITY_NORMAL                ((TThreadPriority)0x02)
#define RVCOS_THREAD_PRIORITY_HIGH                  ((TThreadPriority)0x03)

#define RVCOS_THREAD_ID_INVALID                     ((TThreadID)-1)

#define RVCOS_TIMEOUT_INFINITE                      ((TTick)0)
#define RVCOS_TIMEOUT_IMMEDIATE                     ((TTick)-1)

#define RVCOS_MEMORY_POOL_ID_SYSTEM                 ((TMemoryPoolID)0)
#define RVCOS_MEMORY_POOL_ID_INVALID                ((TMemoryPoolID)-1)

#define RVCOS_MUTEX_ID_INVALID                      ((TMutexID)-1)

#define RVCOS_VIDEO_MODE_TEXT	                    ((TVideoMode)0)
#define RVCOS_VIDEO_MODE_GRAPHICS                   ((TVideoMode)1)

#define RVCOS_GRAPHIC_ID_INVALID                    ((TGraphicID)-1)

#define RVCOS_GRAPHIC_TYPE_FULL                     ((TGraphicType)0)
#define RVCOS_GRAPHIC_TYPE_LARGE                    ((TGraphicType)1)
#define RVCOS_GRAPHIC_TYPE_SMALL                    ((TGraphicType)2)

#define RVCOS_PALETTE_ID_DEFAULT                    ((TPaletteID)0)
#define RVCOS_PALETTE_ID_INVALID                    ((TPaletteID)-1)

typedef uint32_t TStatus, *TStatusRef;
typedef uint32_t TTick, *TTickRef;
typedef int32_t  TThreadReturn, *TThreadReturnRef;
typedef uint32_t TMemorySize, *TMemorySizeRef;
typedef uint32_t TThreadID, *TThreadIDRef;
typedef uint32_t TThreadPriority, *TThreadPriorityRef;
typedef uint32_t TThreadState, *TThreadStateRef;
typedef char     TTextCharacter, *TTextCharacterRef;
typedef uint32_t TMemoryPoolID, *TMemoryPoolIDRef;
typedef uint32_t TMutexID, *TMutexIDRef;
typedef uint32_t TVideoMode, *TVideoModeRef;
typedef uint32_t TGraphicID, *TGraphicIDRef;
typedef uint32_t TGraphicType, *TGraphicTypeRef;
typedef uint32_t TPaletteID, *TPaletteIDRef;
typedef uint8_t TPaletteIndex, *TPaletteIndexRef;

typedef TThreadReturn (*TThreadEntry)(void *);

typedef struct{
    uint32_t DLeft:1;
    uint32_t DUp:1;
    uint32_t DDown:1;
    uint32_t DRight:1;
    uint32_t DButton1:1;
    uint32_t DButton2:1;
    uint32_t DButton3:1;
    uint32_t DButton4:1;
    uint32_t DReserved:24;
} SControllerStatus, *SControllerStatusRef;

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

TStatus RVCInitialize(uint32_t *gp);

TStatus RVCTickMS(uint32_t *tickmsref);
TStatus RVCTickCount(TTickRef tickref);

TStatus RVCThreadCreate(TThreadEntry entry, void *param, TMemorySize memsize, TThreadPriority prio, TThreadIDRef tid);
TStatus RVCThreadDelete(TThreadID thread);
TStatus RVCThreadActivate(TThreadID thread);
TStatus RVCThreadTerminate(TThreadID thread, TThreadReturn returnval);
TStatus RVCThreadWait(TThreadID thread, TThreadReturnRef returnref, TTick timeout);
TStatus RVCThreadID(TThreadIDRef threadref);
TStatus RVCThreadState(TThreadID thread, TThreadStateRef stateref);
TStatus RVCThreadSleep(TTick tick);

#define RVCMemoryAllocate(size,pointer)             RVCMemoryPoolAllocate(RVCOS_MEMORY_POOL_ID_SYSTEM, (size), (pointer))
#define RVCMemoryDeallocate(pointer)                RVCMemoryPoolDeallocate(RVCOS_MEMORY_POOL_ID_SYSTEM, (pointer))
TStatus RVCMemoryPoolCreate(void *base, TMemorySize size, TMemoryPoolIDRef memoryref);
TStatus RVCMemoryPoolDelete(TMemoryPoolID memory);
TStatus RVCMemoryPoolQuery(TMemoryPoolID memory, TMemorySizeRef bytesleft);
TStatus RVCMemoryPoolAllocate(TMemoryPoolID memory, TMemorySize size, void **pointer);
TStatus RVCMemoryPoolDeallocate(TMemoryPoolID memory, void *pointer);

TStatus RVCMutexCreate(TMutexIDRef mutexref);
TStatus RVCMutexDelete(TMutexID mutex);
TStatus RVCMutexQuery(TMutexID mutex, TThreadIDRef ownerref);
TStatus RVCMutexAcquire(TMutexID mutex, TTick timeout);
TStatus RVCMutexRelease(TMutexID mutex);

TStatus RVCWriteText(const TTextCharacter *buffer, TMemorySize writesize);
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

#endif
