#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma region Window

#define WINDOW_CLASS_NAME L"Game Window"
#define WINDOW_TITLE L"Demo"

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

#pragma endregion

#define MAX_FRAME_RATE 60

#define WHITE_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define BLUE_COLOR D3DCOLOR_XRGB(0, 0, 255)

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

#define SAFE_DELETE(p)                                                         \
  if (p != nullptr) {                                                          \
    delete p;                                                                  \
    p = nullptr;                                                               \
  }
#define SAFE_DELETE_ARRAY(p)                                                   \
  if (p != nullptr) {                                                          \
    delete[] p;                                                                \
    p = nullptr;                                                               \
  }
