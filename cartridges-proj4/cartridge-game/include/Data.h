#ifndef DATA_H
#define DATA_H

#include "RVCOS.h"

#define TERRAIN_FRAME_WIDTH         32
#define TERRAIN_FRAME_HEIGHT        32

#define FLOOR_FRAME_COUNT           4
#define WALL_FRAME_COUNT            18

#define HERO_FRAME_WIDTH            64
#define HERO_FRAME_HEIGHT           64

#define HERO_DIRECTIONS             8
#define HERO_FRAMES_PER_DIRECTION   5
#define HERO_FRAME_COUNT            (HERO_DIRECTIONS * HERO_FRAMES_PER_DIRECTION)

#define PALETTE_COLOR_COUNT         256

typedef struct{
    TPaletteIndex DPixels[TERRAIN_FRAME_WIDTH * TERRAIN_FRAME_HEIGHT];
} STerrainFrame, *STerrainFrameRef;

typedef struct{
    STerrainFrame DFrames[FLOOR_FRAME_COUNT];
} SFloorData, *SFloorDataRef;

typedef struct{
    STerrainFrame DFrames[WALL_FRAME_COUNT];
} SWallData, *SWallDataRef;

typedef struct{
    TPaletteIndex DPixels[HERO_FRAME_WIDTH * HERO_FRAME_HEIGHT];
} SHeroFrame, *SHeroFrameRef;

typedef struct{
    SHeroFrame DFrames[HERO_FRAME_COUNT];
} SHeroData, *SHeroDataRef;

extern SColor GamePalette[PALETTE_COLOR_COUNT];
extern SFloorData GameFloorData;
extern SWallData GameWallData;
extern SHeroData GameHeroData;

#endif
