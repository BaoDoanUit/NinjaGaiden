
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//GLOBAL CONSTANT

//view mode(used in contructor of game class)
#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
//
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12


//
//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024


#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox
//
//GLOBAL VARIANT
//
extern int G_CurForm;
extern int G_NextForm;

extern bool			G_IsInitedDX;		//check if dx is inited
extern int			G_GameDepth;		//depth in game class (i dont know
extern char*		G_GameName;		//name of game, view in caption
extern int			G_FrameRate;		//frame rate(30 -> 60)
extern int			G_ColorMode;		//color mode to init dx
extern bool			G_IsFullScreen;	//check if windows or fullscreen
extern D3DFORMAT	G_BackBufferFormat;//backbuffer format, used in initing dx

extern bool			G_HasBackgroundSound;		//check if background music is on
extern bool			G_HasEffectSound;	//check if sound effect is on

extern int			G_MapWidth;			//count the tiles in map width, 1 tile 50px
extern int			G_MapHeight;			//count the tiles in map height, 1 tile 50px

extern int			G_ScreenWidth;			//width of game screen
extern int			G_ScreenHeight;			//height of game screen
extern int          OpeningTheGate;
extern int          Floor;
extern int          AutoFit;
extern int			G_MaxSize;
extern int			G_MinSize;
extern int          State;
extern bool         isBoss;
extern RECT			G_WindowSize;			//size of game screen

extern HINSTANCE					G_hInstance;		// Handle of the game instance
extern HWND							G_hWnd;			// Handle of the Game Window

extern LPDIRECT3D9					G_DirectX;			//handle dx
extern LPDIRECT3DDEVICE9			G_Device;			//dx device
extern LPDIRECT3DSURFACE9			G_BackBuffer;		//backbuffer

extern LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
extern LPDIRECTINPUTDEVICE8			G_KeyBoard;			// The keyboard device 
extern LPD3DXSPRITE					G_SpriteHandler;	// spriteHandler to draw texture

														//GLOBAL METHOD

														//write string to a tracing file
void GLTrace(char* format, ...);

//show a message box
void GLMessage(char* text);

//show string to the caption of window
void GLTitle(char* text);


// ID của Sprite, object
enum eType
{
	NINJAGAIDEN = 01,
	SIMON_TRANS = 02,
	NINJAGAIDEN_DEADTH = 03,

	// object nền
	GROUND = 21,
	

	// enemy
	TORCH = 41,
	OBJECT_HIDDEN = 42,
	BEE = 43,
	BIRD = 44,
	DOG = 45,
	EAGLE = 46,
	ENEMY1 = 47,
	ENEMY2 = 48,
	SITGUN = 49,
	STANDSOLIDER = 50,
	
	//effect 
	EFFECT = 51,



	// weapon
	


	// item
	

	// other
	FONT = 101,
	BOARD = 102,
	BOARDHEALTH = 103,
	MAP3 = 104,
	RENDERBBOX = 105,
	MAP4 = 106,
	BOARD_TRANS = 107,

	// Effect
	FIRE = 121,
	HIT = 122,
	BROKENBRICK = 123,
	STEAM = 124,
	EFFECT_MONEY_700 = 125,
	EFFECT_MONEY_100 = 126,
	EFFECT_MONEY_400 = 127,
	EFFECT_MONEY_1000 = 128,

	//BOSS
	PHANTOMBAT = 161,

	// Intro
	MAINMENU = 181,
	INTRO_GO_SCENE1 = 182,
	INTRO_BAT_MENU = 183, // bat ở menu
	HELICOPTER = 184,
	INTRO_BAT = 185 // ở intro

};

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma region Window

#define WINDOW_CLASS_NAME L"Game Window"
#define WINDOW_TITLE L"Demo"

#define GAME_WIDTH 4096
#define GAME_HEIGHT 352

#pragma endregion

#define MAX_FRAME_RATE 60

#define WHITE_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define BLUE_COLOR D3DCOLOR_XRGB(0, 0, 255)

#define TILE_WIDTH 32	
#define TILE_HEIGHT 32

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

#endif