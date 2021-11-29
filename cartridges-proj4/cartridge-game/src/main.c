#include <stdint.h>
#include <string.h>
#include "RVCOS.h"
#include "Data.h"
#include "Map.h"

#define DEFAULT_COLOR_WHITE     0x0F
#define DEFAULT_COLOR_BLACK     0x10
#define DEFAULT_COLOR_TEAL      0x06
#define SCREEN_WIDTH            0x200
#define SCREEN_HEIGHT           0x120
#define SPRITE_WIDTH            0x10
#define SPRITE_HEIGHT           0x10

#define DIRECTION_NORTH         0
#define DIRECTION_NORTH_EAST    1
#define DIRECTION_EAST          2
#define DIRECTION_SOUTH_EAST    3
#define DIRECTION_SOUTH         4
#define DIRECTION_SOUTH_WEST    5
#define DIRECTION_WEST          6
#define DIRECTION_NORTH_WEST    7

#define STEPS_AT_FRAME          8

typedef struct{
    uint32_t DLevel;
    int32_t DXPosition;
    int32_t DYPosition;
    uint32_t DDirection;
    uint32_t DStep;
    uint32_t DActivatedFrame;
} SHeroState, *SHeroStateRef;

volatile int VideoSynchronized = 0;

void ClearScreen(void);
void WriteString(const char *str);
void FrameDelay(void);
TThreadReturn VideoUpcall(void *);
void ReplaceWallTransparency(void);
void RenderMapLevel(TGraphicID bg, SMapLevelRef map);
void CreateMapLevelBackgrounds(TGraphicIDRef mapbg, SMapLevelRef map);
void CreateHeroFrames(TGraphicIDRef sprites, SHeroDataRef herodata);
void RenderHero(SHeroStateRef herostate, TGraphicIDRef sprites, TPaletteID palette);
int MoveHero(SHeroStateRef herostate,SMapLevelRef maps,SControllerStatusRef controller);
int LocationClear(int x, int y, SMapLevelRef map);
void TransitionLevel(SHeroStateRef herostate,TGraphicIDRef heroframes,SMapLevelRef maps,TGraphicIDRef mapbgs,TPaletteID palette,int dir);

int main() {
    SControllerStatus ControllerStatus;
    TGraphicID MapLevelBackgrounds[MAP_LEVEL_COUNT], HeroFrames[HERO_FRAME_COUNT];
    SGraphicPosition Position;
    SGraphicDimensions Dimensions;
    TPaletteID MainPalette;
    SHeroState HeroState = {0,TERRAIN_FRAME_WIDTH,TERRAIN_FRAME_HEIGHT,DIRECTION_SOUTH,0,HERO_FRAME_COUNT};
    int MoveResult;

    ClearScreen();
    WriteString("Loading Palette: ");
    RVCPaletteCreate(&MainPalette);
    RVCPaletteUpdate(MainPalette,GamePalette,0,PALETTE_COLOR_COUNT);
    WriteString("Done\nLoading Hero: ");
    CreateHeroFrames(HeroFrames,&GameHeroData);
    WriteString("Done\nLoading Levels: ");
    ReplaceWallTransparency();
    CreateMapLevelBackgrounds(MapLevelBackgrounds, MapLevels);
    Position.DXPosition = 0;
    Position.DYPosition = 0;
    Position.DZPosition = 0;
    RVCGraphicActivate(MapLevelBackgrounds[0],&Position,NULL,MainPalette);
    WriteString("Done\nStarting");
    RenderHero(&HeroState,HeroFrames,MainPalette);
    RVCSetVideoUpcall(VideoUpcall,NULL);
    RVCChangeVideoMode(RVCOS_VIDEO_MODE_GRAPHICS);
    
    while(1){
        FrameDelay();
        RVCReadController(&ControllerStatus);
        MoveResult = MoveHero(&HeroState,MapLevels,&ControllerStatus);
        RenderHero(&HeroState,HeroFrames,MainPalette);
        if(MoveResult != -1){
            TransitionLevel(&HeroState,HeroFrames,MapLevels,MapLevelBackgrounds,MainPalette,MoveResult);
        }
    }
    return 0;
}

void ClearScreen(void){
    RVCWriteText("\x1B[2J\x1B[H",7);
}

void WriteString(const char *str){
    uint32_t Length = 0;
    while(str[Length]){
        Length++;
    }
    RVCWriteText(str,Length);
}

void FrameDelay(void){
    while(!VideoSynchronized);
    VideoSynchronized = 0;
}

TThreadReturn VideoUpcall(void *param){
    VideoSynchronized = 1;
}

void ReplaceWallTransparency(void){
    for(int FrameIndex = 0; FrameIndex < WALL_FRAME_COUNT; FrameIndex++){
        for(int PixelIndex = 0; PixelIndex < TERRAIN_FRAME_HEIGHT * TERRAIN_FRAME_WIDTH; PixelIndex++){
            GameWallData.DFrames[FrameIndex].DPixels[PixelIndex] = GameWallData.DFrames[FrameIndex].DPixels[PixelIndex] ? GameWallData.DFrames[FrameIndex].DPixels[PixelIndex] : GameFloorData.DFrames[0].DPixels[PixelIndex];
        }
    }
}

void RenderMapLevel(TGraphicID bg, SMapLevelRef map){
    SGraphicPosition Position;
    SGraphicDimensions Dimensions;

    Dimensions.DHeight = TERRAIN_FRAME_HEIGHT;
    Dimensions.DWidth = TERRAIN_FRAME_HEIGHT;
    for(int YIndex = 0; YIndex < MAP_HEIGHT; YIndex++){
        Position.DYPosition = YIndex * TERRAIN_FRAME_HEIGHT;
        for(int XIndex = 0; XIndex < MAP_WIDTH; XIndex++){
            int FloorIndex = (YIndex * 2 + XIndex & 1) & 3;
            Position.DXPosition = XIndex * TERRAIN_FRAME_WIDTH;
            RVCGraphicDraw(bg,&Position,&Dimensions,GameFloorData.DFrames[FloorIndex].DPixels,TERRAIN_FRAME_WIDTH);
            if(map->DData[YIndex][XIndex] != ' '){
                int WallIndex = 0;
                if(YIndex){
                    WallIndex |= map->DData[YIndex-1][XIndex] == ' ' ? 0 : 1;
                }
                if(XIndex + 1 < MAP_WIDTH){
                    WallIndex |= map->DData[YIndex][XIndex+1] == ' ' ? 0 : 2;
                }
                if(YIndex + 1 < MAP_HEIGHT){
                    WallIndex |= map->DData[YIndex+1][XIndex] == ' ' ? 0 : 4;
                }
                if(XIndex){
                    WallIndex |= map->DData[YIndex][XIndex-1] == ' ' ? 0 : 8;
                }
                if(5 == WallIndex){
                    WallIndex += (YIndex + XIndex) & 0x1;
                }
                else if(10 == WallIndex){
                    WallIndex += (YIndex + XIndex) & 0x1;
                    WallIndex++;

                }   
                else if(10 < WallIndex){
                    WallIndex += 2;
                }
                else if(5 < WallIndex){
                    WallIndex += 1;
                }
                RVCGraphicDraw(bg,&Position,&Dimensions,GameWallData.DFrames[WallIndex].DPixels,TERRAIN_FRAME_WIDTH);
            }
        }
    }
}

void CreateMapLevelBackgrounds(TGraphicIDRef mapbg, SMapLevelRef map){
    for(int Index = 0; Index < MAP_LEVEL_COUNT; Index++){
        RVCGraphicCreate(RVCOS_GRAPHIC_TYPE_FULL,mapbg+Index);
        RenderMapLevel(mapbg[Index],map+Index);
    }
}

void CreateHeroFrames(TGraphicIDRef sprites, SHeroDataRef herodata){
    SGraphicPosition Position;
    SGraphicDimensions Dimensions;
    Dimensions.DHeight = HERO_FRAME_HEIGHT;
    Dimensions.DWidth = HERO_FRAME_WIDTH;
    Position.DXPosition = 0;
    Position.DYPosition = 0;
    for(int Index = 0; Index < HERO_FRAME_COUNT; Index++){
        RVCGraphicCreate(RVCOS_GRAPHIC_TYPE_LARGE,sprites+Index);
        RVCGraphicDraw(sprites[Index],&Position,&Dimensions,herodata->DFrames[Index].DPixels,HERO_FRAME_WIDTH);
    }
}

void RenderHero(SHeroStateRef herostate, TGraphicIDRef sprites, TPaletteID palette){
    SGraphicPosition Position;
    SGraphicDimensions Dimensions;
    Dimensions.DHeight = HERO_FRAME_HEIGHT;
    Dimensions.DWidth = HERO_FRAME_WIDTH;
    

    if(herostate->DActivatedFrame < HERO_FRAME_COUNT){
        RVCGraphicDeactivate(sprites[herostate->DActivatedFrame]);
    }
    herostate->DActivatedFrame = herostate->DDirection * HERO_FRAMES_PER_DIRECTION + herostate->DStep / STEPS_AT_FRAME;
    Position.DXPosition = herostate->DXPosition - HERO_FRAME_WIDTH/4;
    Position.DYPosition = herostate->DYPosition - HERO_FRAME_HEIGHT/4;
    Position.DZPosition = 4;
     
    // Z position doesn't matter because large sprite
    RVCGraphicActivate(sprites[herostate->DActivatedFrame],&Position,&Dimensions,palette);   
}

int MoveHero(SHeroStateRef herostate,SMapLevelRef maps,SControllerStatusRef controller){
    int CurrentX, CurrentY;
    int DeltaX = 0, DeltaY = 0;
    int Direction = -1;
    CurrentX = herostate->DXPosition / TERRAIN_FRAME_WIDTH;
    CurrentY = herostate->DYPosition / TERRAIN_FRAME_HEIGHT;
    if(controller->DUp && !controller->DDown){
        DeltaY = -1;
        Direction = DIRECTION_NORTH;
    }
    else if(!controller->DUp && controller->DDown){
        DeltaY = 1;
        Direction = DIRECTION_SOUTH;
    }
    if(controller->DLeft && !controller->DRight){
        DeltaX = -1;
        Direction = Direction == -1 ? DIRECTION_WEST : (Direction + DeltaY + 8) % 8;
    }
    else if(!controller->DLeft && controller->DRight){
        DeltaX = 1;
        Direction = Direction == -1 ? DIRECTION_EAST : (Direction - DeltaY + 8) % 8;
    }
    if(0 <= Direction){
        int NewX, NewY, NewXMod, NewYMod;
        int CanMove = 0;
        NewX = herostate->DXPosition + DeltaX;
        NewXMod = NewX % TERRAIN_FRAME_WIDTH;
        NewY = herostate->DYPosition + DeltaY;
        NewYMod = NewY % TERRAIN_FRAME_HEIGHT;
        if(herostate->DDirection == Direction){
            herostate->DStep++;
            herostate->DStep %= HERO_FRAMES_PER_DIRECTION * STEPS_AT_FRAME;
        }
        herostate->DDirection = Direction;
        
        if(LocationClear(NewX,NewY,maps+herostate->DLevel)){
            herostate->DXPosition = NewX;
            herostate->DYPosition = NewY;
        }
        else if(DeltaX * DeltaY){
            if(LocationClear(herostate->DXPosition,NewY,maps+herostate->DLevel)){
                herostate->DYPosition = NewY;
            }
            else if(LocationClear(NewX,herostate->DYPosition,maps+herostate->DLevel)){
                herostate->DXPosition = NewX;
            }
        }
    }
    else{
        herostate->DStep = 0;
    }
    if(0 > herostate->DXPosition){
        return DIRECTION_WEST;
    }
    if(0 > herostate->DYPosition){
        return DIRECTION_NORTH;
    }
    if(herostate->DXPosition + TERRAIN_FRAME_WIDTH > SCREEN_WIDTH){
        return DIRECTION_EAST;
    }
    if(herostate->DYPosition + TERRAIN_FRAME_HEIGHT > SCREEN_HEIGHT){
        return DIRECTION_SOUTH;
    }
    return -1;
}

int LocationClear(int x, int y, SMapLevelRef map){
    int LeftX = x / TERRAIN_FRAME_WIDTH;
    int TopY = y / TERRAIN_FRAME_HEIGHT;
    int XMod = x % TERRAIN_FRAME_WIDTH;
    int YMod = y % TERRAIN_FRAME_HEIGHT;
    if(map->DData[TopY][LeftX] != ' '){
        return 0;
    }
    if(XMod){
        if((LeftX + 1 < MAP_WIDTH)&&(map->DData[TopY][LeftX+1] != ' ')){
            return 0;
        }
    }
    if(YMod){
        if((TopY + 1 < MAP_HEIGHT)&&(map->DData[TopY+1][LeftX] != ' ')){
            return 0;
        }
    }
    if(XMod && YMod){
        if((LeftX + 1 < MAP_WIDTH)&&(TopY + 1 < MAP_HEIGHT)&&(map->DData[TopY+1][LeftX+1] != ' ')){
            return 0;
        }
    }
    return 1;
}

void TransitionLevel(SHeroStateRef herostate,TGraphicIDRef heroframes,SMapLevelRef maps,TGraphicIDRef mapbgs,TPaletteID pal,int dir){
    int DeltaX = 0, DeltaY = 0;
    int OtherX = 0, OtherY = 0;
    int CurrentLevel = herostate->DLevel;
    int NextLevel = CurrentLevel;
    switch(dir){
        case DIRECTION_NORTH:   DeltaY = 1;
                                OtherY = -SCREEN_HEIGHT;
                                NextLevel = maps[CurrentLevel].DUpIndex;
                                break;
        case DIRECTION_EAST:    DeltaX = -1;
                                OtherX = SCREEN_WIDTH;
                                NextLevel = maps[CurrentLevel].DRightIndex;
                                break;
        case DIRECTION_SOUTH:   DeltaY = -1;
                                OtherY = SCREEN_HEIGHT;
                                NextLevel = maps[CurrentLevel].DDownIndex;
                                break;
        case DIRECTION_WEST:    DeltaX = 1;
                                OtherX = -SCREEN_WIDTH;
                                NextLevel = maps[CurrentLevel].DLeftIndex;
                                break;
    }
    SGraphicPosition CurrentPosition, OtherPosition;
    CurrentPosition.DXPosition = CurrentPosition.DYPosition = CurrentPosition.DZPosition = 0;
    OtherPosition.DXPosition = OtherX;
    OtherPosition.DYPosition = OtherY;
    OtherPosition.DZPosition = 0;
    while(OtherPosition.DXPosition || OtherPosition.DYPosition){
        FrameDelay();
        CurrentPosition.DXPosition += DeltaX;
        CurrentPosition.DYPosition += DeltaY;
        OtherPosition.DXPosition += DeltaX;
        OtherPosition.DYPosition += DeltaY;
        herostate->DXPosition += DeltaX;
        herostate->DYPosition += DeltaY;
        RVCGraphicActivate(mapbgs[CurrentLevel],&CurrentPosition,NULL,pal);
        RVCGraphicActivate(mapbgs[NextLevel],&OtherPosition,NULL,pal);
        RenderHero(herostate,heroframes,pal);
    }
    RVCGraphicDeactivate(mapbgs[CurrentLevel]);
    DeltaX = -DeltaX;
    DeltaY = -DeltaY;
    while((herostate->DXPosition % TERRAIN_FRAME_WIDTH) || (herostate->DYPosition % TERRAIN_FRAME_HEIGHT)){
        FrameDelay();
        herostate->DXPosition += DeltaX;
        herostate->DYPosition += DeltaY;
        herostate->DStep++;
        herostate->DStep %= HERO_FRAMES_PER_DIRECTION * STEPS_AT_FRAME;
        RenderHero(herostate,heroframes,pal);
    }
    herostate->DLevel = NextLevel;
    //while(1);
}