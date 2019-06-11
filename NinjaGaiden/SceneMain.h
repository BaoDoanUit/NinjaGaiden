#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Dog.h"
#include "Eagle.h"
#include "Game.h"
#include "NinjaGaiden.h"
#include "Objects/Map/Map.h"
#include "Grid.h"
class SceneMain : public Game {
public:
  NinjaGaiden *ninjaGaiden;
  Camera *cam, *camDog;
  Eagle *eagle;
  Dog *dog;
  Grid* gridGame;
  vector<BaseObject*> listObj;
  vector<BaseObject*> listEnemy;
  vector<BaseObject*> listGround;
  vector<BaseObject*> listItem;
  int CollectMorningStar = 0;
  vector<Weapon*> weapons;
  int PreUpStair;
  int PreDownStair;

  bool lockKeyboard = 0;
  bool isPlay_Exit = true;

  int minT = 0;
  int minC = 0; // vong lap thoi gian cho diem tang;
  int minS = 0; // vong lap thoi gian chuan bi khoa phim;
  int minD = 0; // dem thoi gian chuan bi reset

  bool stopNinjaGaiden = false;
  bool isOpenTheGate = false;

  // --

  Map *pMap;

  SceneMain(int nCmdShow);
  ~SceneMain();

protected:
  // Render
  void UpdateObject(Camera *cam, int t);
  virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
  void RenderStage(LPDIRECT3DDEVICE9 d3ddv, int t);
  virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
  void LoadMap1();
  void LoadMap2();
  void LoadMap3();

  virtual void OnKeyDown(int KeyCode);
  virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
  void ResetResource();
  void LoadComponent();
  void CheckCollision();
  void CheckCollisionEnemy();
  void CheckCollisionGround();
  void CheckCollisionItem();
};

#endif