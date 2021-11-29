#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH           16
#define MAP_HEIGHT          9
#define MAP_LEVEL_COUNT     4

typedef struct{
    int DUpIndex;
    int DDownIndex;
    int DRightIndex;
    int DLeftIndex;
    char DData[MAP_HEIGHT][MAP_WIDTH+1];
} SMapLevel, *SMapLevelRef;

extern SMapLevel MapLevels[MAP_LEVEL_COUNT];

#endif
