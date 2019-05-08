#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Game.h"
#include "NinjaGaiden.h"
class SceneMain : public Game
{
public:
	NinjaGaiden *ninjaGaiden;
	Camera *cam;

	int CollectMorningStar = 0;

	int PreUpStair;
	int PreDownStair;

	bool lockKeyboard = 0;
	bool isPlay_Exit = true;

	int minT = 0;
	int minC = 0;//vong lap thoi gian cho diem tang;
	int minS = 0;//vong lap thoi gian chuan bi khoa phim;
	int minD = 0;// dem thoi gian chuan bi reset

	bool stopNinjaGaiden = false;
	bool isOpenTheGate = false;

	SceneMain(int nCmdShow);
	~SceneMain();
protected:
	// Render
	void UpdateObject(Camera * cam, int t);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void RenderStage(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void LoadMap1();
	void LoadMap2();
	void LoadMap3();
	

	virtual void OnKeyDown(int KeyCode);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

};

#endif