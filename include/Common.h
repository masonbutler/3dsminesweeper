#ifndef _COMMON_H_
#define _COMMON_H_


constexpr int TILE_SIZE                     = 16;

constexpr int TOP_SCREEN_WIDTH_PIXELS       = 400;
constexpr int TOP_SCREEN_HEIGHT_PIXELS      = 240;
constexpr int TOP_SCREEN_WIDTH_TILES        = (TOP_SCREEN_WIDTH_PIXELS / TILE_SIZE);
constexpr int TOP_SCREEN_HEIGHT_TILE        = (TOP_SCREEN_HEIGHT_PIXELS / TILE_SIZE);

constexpr int BOTTOM_SCREEN_WIDTH_PIXELS    = 320;
constexpr int BOTTOM_SCREEN_HEIGHT_PIXELS   = 240;
constexpr int BOTTOM_SCREEN_WIDTH_TILES     = (BOTTOM_SCREEN_WIDTH_PIXELS / TILE_SIZE);
constexpr int BOTTOM_SCREEN_HEIGHT_TILE     = (BOTTOM_SCREEN_HEIGHT_PIXELS / TILE_SIZE);

constexpr int MAX_WIDTH_TILES               = 22;
constexpr int MAX_HEIGHT_TILES              = 14;

constexpr int OFFSET_DISTANCE_3D            = 20;

constexpr int OFFSET_BG_3D                  = 2;
constexpr int OFFSET_TILE_3D                = 1;
constexpr int OFFSET_FG_3D                  = 0;


#endif