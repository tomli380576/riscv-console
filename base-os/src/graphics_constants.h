#include "RVCOS.h"

const Palette RVCOPaletteDefaultColors = {
{0x00, 0x00, 0x00, 0x00}, // Transparent
{0x00, 0x00, 0x80, 0xFF}, // Maroon (SYSTEM)
{0x00, 0x80, 0x00, 0xFF}, // Green (SYSTEM)
{0x00, 0x80, 0x80, 0xFF}, // Olive (SYSTEM)
{0x80, 0x00, 0x00, 0xFF}, // Navy (SYSTEM)
{0x80, 0x00, 0x80, 0xFF}, // Purple (SYSTEM)
{0x80, 0x80, 0x00, 0xFF}, // Teal (SYSTEM)
{0xC0, 0xC0, 0xC0, 0xFF}, // Silver (SYSTEM)
{0x80, 0x80, 0x80, 0xFF}, // Grey (SYSTEM)
{0x00, 0x00, 0xFF, 0xFF}, // Red (SYSTEM)
{0x00, 0xFF, 0x00, 0xFF}, // Lime (SYSTEM)
{0x00, 0xFF, 0xFF, 0xFF}, // Yellow (SYSTEM)
{0xFF, 0x00, 0x00, 0xFF}, // Blue (SYSTEM)
{0xFF, 0x00, 0xFF, 0xFF}, // Fuchsia (SYSTEM)
{0xFF, 0xFF, 0x00, 0xFF}, // Aqua (SYSTEM)
{0xFF, 0xFF, 0xFF, 0xFF}, // White (SYSTEM)
{0x00, 0x00, 0x00, 0xFF}, // Black (SYSTEM)
{0x5F, 0x00, 0x00, 0xFF}, // NavyBlue
{0x87, 0x00, 0x00, 0xFF}, // DarkBlue
{0xAF, 0x00, 0x00, 0xFF}, // Blue3
{0xD7, 0x00, 0x00, 0xFF}, // Blue3
{0xFF, 0x00, 0x00, 0xFF}, // Blue1
{0x00, 0x5F, 0x00, 0xFF}, // DarkGreen
{0x5F, 0x5F, 0x00, 0xFF}, // DeepSkyBlue4
{0x87, 0x5F, 0x00, 0xFF}, // DeepSkyBlue4
{0xAF, 0x5F, 0x00, 0xFF}, // DeepSkyBlue4
{0xD7, 0x5F, 0x00, 0xFF}, // DodgerBlue3
{0xFF, 0x5F, 0x00, 0xFF}, // DodgerBlue2
{0x00, 0x87, 0x00, 0xFF}, // Green4
{0x5F, 0x87, 0x00, 0xFF}, // SpringGreen4
{0x87, 0x87, 0x00, 0xFF}, // Turquoise4
{0xAF, 0x87, 0x00, 0xFF}, // DeepSkyBlue3
{0xD7, 0x87, 0x00, 0xFF}, // DeepSkyBlue3
{0xFF, 0x87, 0x00, 0xFF}, // DodgerBlue1
{0x00, 0xAF, 0x00, 0xFF}, // Green3
{0x5F, 0xAF, 0x00, 0xFF}, // SpringGreen3
{0x87, 0xAF, 0x00, 0xFF}, // DarkCyan
{0xAF, 0xAF, 0x00, 0xFF}, // LightSeaGreen
{0xD7, 0xAF, 0x00, 0xFF}, // DeepSkyBlue2
{0xFF, 0xAF, 0x00, 0xFF}, // DeepSkyBlue1
{0x00, 0xD7, 0x00, 0xFF}, // Green3
{0x5F, 0xD7, 0x00, 0xFF}, // SpringGreen3
{0x87, 0xD7, 0x00, 0xFF}, // SpringGreen2
{0xAF, 0xD7, 0x00, 0xFF}, // Cyan3
{0xD7, 0xD7, 0x00, 0xFF}, // DarkTurquoise
{0xFF, 0xD7, 0x00, 0xFF}, // Turquoise2
{0x00, 0xFF, 0x00, 0xFF}, // Green1
{0x5F, 0xFF, 0x00, 0xFF}, // SpringGreen2
{0x87, 0xFF, 0x00, 0xFF}, // SpringGreen1
{0xAF, 0xFF, 0x00, 0xFF}, // MediumSpringGreen
{0xD7, 0xFF, 0x00, 0xFF}, // Cyan2
{0xFF, 0xFF, 0x00, 0xFF}, // Cyan1
{0x00, 0x00, 0x5F, 0xFF}, // DarkRed
{0x5F, 0x00, 0x5F, 0xFF}, // DeepPink4
{0x87, 0x00, 0x5F, 0xFF}, // Purple4
{0xAF, 0x00, 0x5F, 0xFF}, // Purple4
{0xD7, 0x00, 0x5F, 0xFF}, // Purple3
{0xFF, 0x00, 0x5F, 0xFF}, // BlueViolet
{0x00, 0x5F, 0x5F, 0xFF}, // Orange4
{0x5F, 0x5F, 0x5F, 0xFF}, // Grey37
{0x87, 0x5F, 0x5F, 0xFF}, // MediumPurple4
{0xAF, 0x5F, 0x5F, 0xFF}, // SlateBlue3
{0xD7, 0x5F, 0x5F, 0xFF}, // SlateBlue3
{0xFF, 0x5F, 0x5F, 0xFF}, // RoyalBlue1
{0x00, 0x87, 0x5F, 0xFF}, // Chartreuse4
{0x5F, 0x87, 0x5F, 0xFF}, // DarkSeaGreen4
{0x87, 0x87, 0x5F, 0xFF}, // PaleTurquoise4
{0xAF, 0x87, 0x5F, 0xFF}, // SteelBlue
{0xD7, 0x87, 0x5F, 0xFF}, // SteelBlue3
{0xFF, 0x87, 0x5F, 0xFF}, // CornflowerBlue
{0x00, 0xAF, 0x5F, 0xFF}, // Chartreuse3
{0x5F, 0xAF, 0x5F, 0xFF}, // DarkSeaGreen4
{0x87, 0xAF, 0x5F, 0xFF}, // CadetBlue
{0xAF, 0xAF, 0x5F, 0xFF}, // CadetBlue
{0xD7, 0xAF, 0x5F, 0xFF}, // SkyBlue3
{0xFF, 0xAF, 0x5F, 0xFF}, // SteelBlue1
{0x00, 0xD7, 0x5F, 0xFF}, // Chartreuse3
{0x5F, 0xD7, 0x5F, 0xFF}, // PaleGreen3
{0x87, 0xD7, 0x5F, 0xFF}, // SeaGreen3
{0xAF, 0xD7, 0x5F, 0xFF}, // Aquamarine3
{0xD7, 0xD7, 0x5F, 0xFF}, // MediumTurquoise
{0xFF, 0xD7, 0x5F, 0xFF}, // SteelBlue1
{0x00, 0xFF, 0x5F, 0xFF}, // Chartreuse2
{0x5F, 0xFF, 0x5F, 0xFF}, // SeaGreen2
{0x87, 0xFF, 0x5F, 0xFF}, // SeaGreen1
{0xAF, 0xFF, 0x5F, 0xFF}, // SeaGreen1
{0xD7, 0xFF, 0x5F, 0xFF}, // Aquamarine1
{0xFF, 0xFF, 0x5F, 0xFF}, // DarkSlateGray2
{0x00, 0x00, 0x87, 0xFF}, // DarkRed
{0x5F, 0x00, 0x87, 0xFF}, // DeepPink4
{0x87, 0x00, 0x87, 0xFF}, // DarkMagenta
{0xAF, 0x00, 0x87, 0xFF}, // DarkMagenta
{0xD7, 0x00, 0x87, 0xFF}, // DarkViolet
{0xFF, 0x00, 0x87, 0xFF}, // Purple
{0x00, 0x5F, 0x87, 0xFF}, // Orange4
{0x5F, 0x5F, 0x87, 0xFF}, // LightPink4
{0x87, 0x5F, 0x87, 0xFF}, // Plum4
{0xAF, 0x5F, 0x87, 0xFF}, // MediumPurple3
{0xD7, 0x5F, 0x87, 0xFF}, // MediumPurple3
{0xFF, 0x5F, 0x87, 0xFF}, // SlateBlue1
{0x00, 0x87, 0x87, 0xFF}, // Yellow4
{0x5F, 0x87, 0x87, 0xFF}, // Wheat4
{0x87, 0x87, 0x87, 0xFF}, // Grey53
{0xAF, 0x87, 0x87, 0xFF}, // LightSlateGrey
{0xD7, 0x87, 0x87, 0xFF}, // MediumPurple
{0xFF, 0x87, 0x87, 0xFF}, // LightSlateBlue
{0x00, 0xAF, 0x87, 0xFF}, // Yellow4
{0x5F, 0xAF, 0x87, 0xFF}, // DarkOliveGreen3
{0x87, 0xAF, 0x87, 0xFF}, // DarkSeaGreen
{0xAF, 0xAF, 0x87, 0xFF}, // LightSkyBlue3
{0xD7, 0xAF, 0x87, 0xFF}, // LightSkyBlue3
{0xFF, 0xAF, 0x87, 0xFF}, // SkyBlue2
{0x00, 0xD7, 0x87, 0xFF}, // Chartreuse2
{0x5F, 0xD7, 0x87, 0xFF}, // DarkOliveGreen3
{0x87, 0xD7, 0x87, 0xFF}, // PaleGreen3
{0xAF, 0xD7, 0x87, 0xFF}, // DarkSeaGreen3
{0xD7, 0xD7, 0x87, 0xFF}, // DarkSlateGray3
{0xFF, 0xD7, 0x87, 0xFF}, // SkyBlue1
{0x00, 0xFF, 0x87, 0xFF}, // Chartreuse1
{0x5F, 0xFF, 0x87, 0xFF}, // LightGreen
{0x87, 0xFF, 0x87, 0xFF}, // LightGreen
{0xAF, 0xFF, 0x87, 0xFF}, // PaleGreen1
{0xD7, 0xFF, 0x87, 0xFF}, // Aquamarine1
{0xFF, 0xFF, 0x87, 0xFF}, // DarkSlateGray1
{0x00, 0x00, 0xAF, 0xFF}, // Red3
{0x5F, 0x00, 0xAF, 0xFF}, // DeepPink4
{0x87, 0x00, 0xAF, 0xFF}, // MediumVioletRed
{0xAF, 0x00, 0xAF, 0xFF}, // Magenta3
{0xD7, 0x00, 0xAF, 0xFF}, // DarkViolet
{0xFF, 0x00, 0xAF, 0xFF}, // Purple
{0x00, 0x5F, 0xAF, 0xFF}, // DarkOrange3
{0x5F, 0x5F, 0xAF, 0xFF}, // IndianRed
{0x87, 0x5F, 0xAF, 0xFF}, // HotPink3
{0xAF, 0x5F, 0xAF, 0xFF}, // MediumOrchid3
{0xD7, 0x5F, 0xAF, 0xFF}, // MediumOrchid
{0xFF, 0x5F, 0xAF, 0xFF}, // MediumPurple2
{0x00, 0x87, 0xAF, 0xFF}, // DarkGoldenrod
{0x5F, 0x87, 0xAF, 0xFF}, // LightSalmon3
{0x87, 0x87, 0xAF, 0xFF}, // RosyBrown
{0xAF, 0x87, 0xAF, 0xFF}, // Grey63
{0xD7, 0x87, 0xAF, 0xFF}, // MediumPurple2
{0xFF, 0x87, 0xAF, 0xFF}, // MediumPurple1
{0x00, 0xAF, 0xAF, 0xFF}, // Gold3
{0x5F, 0xAF, 0xAF, 0xFF}, // DarkKhaki
{0x87, 0xAF, 0xAF, 0xFF}, // NavajoWhite3
{0xAF, 0xAF, 0xAF, 0xFF}, // Grey69
{0xD7, 0xAF, 0xAF, 0xFF}, // LightSteelBlue3
{0xFF, 0xAF, 0xAF, 0xFF}, // LightSteelBlue
{0x00, 0xD7, 0xAF, 0xFF}, // Yellow3
{0x5F, 0xD7, 0xAF, 0xFF}, // DarkOliveGreen3
{0x87, 0xD7, 0xAF, 0xFF}, // DarkSeaGreen3
{0xAF, 0xD7, 0xAF, 0xFF}, // DarkSeaGreen2
{0xD7, 0xD7, 0xAF, 0xFF}, // LightCyan3
{0xFF, 0xD7, 0xAF, 0xFF}, // LightSkyBlue1
{0x00, 0xFF, 0xAF, 0xFF}, // GreenYellow
{0x5F, 0xFF, 0xAF, 0xFF}, // DarkOliveGreen2
{0x87, 0xFF, 0xAF, 0xFF}, // PaleGreen1
{0xAF, 0xFF, 0xAF, 0xFF}, // DarkSeaGreen2
{0xD7, 0xFF, 0xAF, 0xFF}, // DarkSeaGreen1
{0xFF, 0xFF, 0xAF, 0xFF}, // PaleTurquoise1
{0x00, 0x00, 0xD7, 0xFF}, // Red3
{0x5F, 0x00, 0xD7, 0xFF}, // DeepPink3
{0x87, 0x00, 0xD7, 0xFF}, // DeepPink3
{0xAF, 0x00, 0xD7, 0xFF}, // Magenta3
{0xD7, 0x00, 0xD7, 0xFF}, // Magenta3
{0xFF, 0x00, 0xD7, 0xFF}, // Magenta2
{0x00, 0x5F, 0xD7, 0xFF}, // DarkOrange3
{0x5F, 0x5F, 0xD7, 0xFF}, // IndianRed
{0x87, 0x5F, 0xD7, 0xFF}, // HotPink3
{0xAF, 0x5F, 0xD7, 0xFF}, // HotPink2
{0xD7, 0x5F, 0xD7, 0xFF}, // Orchid
{0xFF, 0x5F, 0xD7, 0xFF}, // MediumOrchid1
{0x00, 0x87, 0xD7, 0xFF}, // Orange3
{0x5F, 0x87, 0xD7, 0xFF}, // LightSalmon3
{0x87, 0x87, 0xD7, 0xFF}, // LightPink3
{0xAF, 0x87, 0xD7, 0xFF}, // Pink3
{0xD7, 0x87, 0xD7, 0xFF}, // Plum3
{0xFF, 0x87, 0xD7, 0xFF}, // Violet
{0x00, 0xAF, 0xD7, 0xFF}, // Gold3
{0x5F, 0xAF, 0xD7, 0xFF}, // LightGoldenrod3
{0x87, 0xAF, 0xD7, 0xFF}, // Tan
{0xAF, 0xAF, 0xD7, 0xFF}, // MistyRose3
{0xD7, 0xAF, 0xD7, 0xFF}, // Thistle3
{0xFF, 0xAF, 0xD7, 0xFF}, // Plum2
{0x00, 0xD7, 0xD7, 0xFF}, // Yellow3
{0x5F, 0xD7, 0xD7, 0xFF}, // Khaki3
{0x87, 0xD7, 0xD7, 0xFF}, // LightGoldenrod2
{0xAF, 0xD7, 0xD7, 0xFF}, // LightYellow3
{0xD7, 0xD7, 0xD7, 0xFF}, // Grey84
{0xFF, 0xD7, 0xD7, 0xFF}, // LightSteelBlue1
{0x00, 0xFF, 0xD7, 0xFF}, // Yellow2
{0x5F, 0xFF, 0xD7, 0xFF}, // DarkOliveGreen1
{0x87, 0xFF, 0xD7, 0xFF}, // DarkOliveGreen1
{0xAF, 0xFF, 0xD7, 0xFF}, // DarkSeaGreen1
{0xD7, 0xFF, 0xD7, 0xFF}, // Honeydew2
{0xFF, 0xFF, 0xD7, 0xFF}, // LightCyan1
{0x00, 0x00, 0xFF, 0xFF}, // Red1
{0x5F, 0x00, 0xFF, 0xFF}, // DeepPink2
{0x87, 0x00, 0xFF, 0xFF}, // DeepPink1
{0xAF, 0x00, 0xFF, 0xFF}, // DeepPink1
{0xD7, 0x00, 0xFF, 0xFF}, // Magenta2
{0xFF, 0x00, 0xFF, 0xFF}, // Magenta1
{0x00, 0x5F, 0xFF, 0xFF}, // OrangeRed1
{0x5F, 0x5F, 0xFF, 0xFF}, // IndianRed1
{0x87, 0x5F, 0xFF, 0xFF}, // IndianRed1
{0xAF, 0x5F, 0xFF, 0xFF}, // HotPink
{0xD7, 0x5F, 0xFF, 0xFF}, // HotPink
{0xFF, 0x5F, 0xFF, 0xFF}, // MediumOrchid1
{0x00, 0x87, 0xFF, 0xFF}, // DarkOrange
{0x5F, 0x87, 0xFF, 0xFF}, // Salmon1
{0x87, 0x87, 0xFF, 0xFF}, // LightCoral
{0xAF, 0x87, 0xFF, 0xFF}, // PaleVioletRed1
{0xD7, 0x87, 0xFF, 0xFF}, // Orchid2
{0xFF, 0x87, 0xFF, 0xFF}, // Orchid1
{0x00, 0xAF, 0xFF, 0xFF}, // Orange1
{0x5F, 0xAF, 0xFF, 0xFF}, // SandyBrown
{0x87, 0xAF, 0xFF, 0xFF}, // LightSalmon1
{0xAF, 0xAF, 0xFF, 0xFF}, // LightPink1
{0xD7, 0xAF, 0xFF, 0xFF}, // Pink1
{0xFF, 0xAF, 0xFF, 0xFF}, // Plum1
{0x00, 0xD7, 0xFF, 0xFF}, // Gold1
{0x5F, 0xD7, 0xFF, 0xFF}, // LightGoldenrod2
{0x87, 0xD7, 0xFF, 0xFF}, // LightGoldenrod2
{0xAF, 0xD7, 0xFF, 0xFF}, // NavajoWhite1
{0xD7, 0xD7, 0xFF, 0xFF}, // MistyRose1
{0xFF, 0xD7, 0xFF, 0xFF}, // Thistle1
{0x00, 0xFF, 0xFF, 0xFF}, // Yellow1
{0x5F, 0xFF, 0xFF, 0xFF}, // LightGoldenrod1
{0x87, 0xFF, 0xFF, 0xFF}, // Khaki1
{0xAF, 0xFF, 0xFF, 0xFF}, // Wheat1
{0xD7, 0xFF, 0xFF, 0xFF}, // Cornsilk1
{0xFF, 0xFF, 0xFF, 0xFF}, // Grey100
{0x08, 0x08, 0x08, 0xFF}, // Grey3
{0x12, 0x12, 0x12, 0xFF}, // Grey7
{0x1C, 0x1C, 0x1C, 0xFF}, // Grey11
{0x26, 0x26, 0x26, 0xFF}, // Grey15
{0x30, 0x30, 0x30, 0xFF}, // Grey19
{0x3A, 0x3A, 0x3A, 0xFF}, // Grey23
{0x44, 0x44, 0x44, 0xFF}, // Grey27
{0x4E, 0x4E, 0x4E, 0xFF}, // Grey30
{0x58, 0x58, 0x58, 0xFF}, // Grey35
{0x62, 0x62, 0x62, 0xFF}, // Grey39
{0x6C, 0x6C, 0x6C, 0xFF}, // Grey42
{0x76, 0x76, 0x76, 0xFF}, // Grey46
{0x80, 0x80, 0x80, 0xFF}, // Grey50
{0x8A, 0x8A, 0x8A, 0xFF}, // Grey54
{0x94, 0x94, 0x94, 0xFF}, // Grey58
{0x9E, 0x9E, 0x9E, 0xFF}, // Grey62
{0xA8, 0xA8, 0xA8, 0xFF}, // Grey66
{0xB2, 0xB2, 0xB2, 0xFF}, // Grey70
{0xBC, 0xBC, 0xBC, 0xFF}, // Grey74
{0xC6, 0xC6, 0xC6, 0xFF}, // Grey78
{0xD0, 0xD0, 0xD0, 0xFF}, // Grey82
{0xDA, 0xDA, 0xDA, 0xFF}, // Grey85
{0xE4, 0xE4, 0xE4, 0xFF}, // Grey89
{0xEE, 0xEE, 0xEE, 0xFF}  // Grey93
};