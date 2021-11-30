#include "Map.h"


SMapLevel MapLevels[MAP_LEVEL_COUNT] = {
    {
    -1,-1,1,-1,
    {
        "XXXXXXXXXXXXXXXX",
        "X X   X   X    X",
        "X X X X X X    X",
        "X X X   X X    X",
        "X   XXXXX X     ",
        "X X            X",
        "X XX XXXX X    X",
        "X    X    X    X",
        "XXXXXXXXXXXXXXXX"
    }
    },
    {
    -1,2,-1,0,
    {
        "XXXXXXXXXXXXXXXX",
        "X     X     X  X",
        "X XX  X X X X  X",
        "X X   X X X X  X",
        "  X XXXXX X X  X",
        "XXX  X    X X  X",
        "X XX XXXX X    X",
        "X         X X  X",
        "XXXXXXXXXXXXXX X"
    }
    },
    {
    1,-1,-1,3,
    {
        "XXXXXXXXXXXXXX X",
        "  X     X   X  X",
        "X XX  X X X X  X",
        "X     X X X X  X",
        "XXXXXXX X X X  X",
        "X       X X X  X",
        "X XXXXXXX X X  X",
        "X         X    X",
        "XXXXXXXXXXXXXXXX"
    }
    },
    {
    -1,-1,2,-1,
    {
        "XXXXXXXXXXXXXXXX",
        "X X     X       ",
        "X XXX X X X XXXX",
        "X     X X X X  X",
        "X XXXXX X X X  X",
        "X X     X X X  X",
        "X X XXXXX X X  X",
        "X X       X    X",
        "XXXXXXXXXXXXXXXX"
    }
    }
};