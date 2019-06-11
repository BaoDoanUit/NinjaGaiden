#ifndef __GRID_H__
#define	__GRID_H__

#include "Game.h" 
#include "Sprite.h"  

#include "Global.h"
#include "Dog.h"
#include "Enemy1.h"
#include "Bird.h"
#include "Bee.h"
#include "Eagle.h"
#include "Enemy2.h"
#include "SitGun.h"
#include "StandSolider.h"
#include "Ground.h"

using namespace std;



#define GRID_CELL_WIDTH (GAME_WIDTH/16.0f)
#define GRID_CELL_HEIGHT (GAME_HEIGHT/4.0f)

#define GRID_INSERT_OBJECT__DIXUONGHONUOC_LEFT 41, eType::OBJECT_HIDDEN, -1, 3190 ,423, 40, 10, 0 // object ẩn đụng vào sẽ đi xuống hồ nước, phía trái
#define GRID_INSERT_OBJECT__DIRAKHOIHONUOC_LEFT 45, eType::OBJECT_HIDDEN, -1, 3135, 435, 20, 20, 0 // object ẩn đụng vào sẽ đi ra khỏi hồ nước, phía trái

#define GRID_INSERT_OBJECT__DIXUONGHONUOC_RIGHT 86, eType::OBJECT_HIDDEN, -1, 3835, 423, 25, 10, 0 // object ẩn đụng vào sẽ đi ra khỏi hồ nước, phía trái
#define GRID_INSERT_OBJECT__DIRAKHOIHONUOC_RIGHT 81, eType::OBJECT_HIDDEN, -1, 3807, 460, 30, 20, 0 // object ẩn đụng vào sẽ đi ra khỏi hồ nước, phía trái

#define GRID_CELL_MAX_ROW 20 // số dòng tối đa;
#define GRID_CELL_MAX_COLUMN 100 // số cột tối đa


class Grid
{
private:
	vector<BaseObject*> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN];
	char * filepath;

public:
	Grid();
	~Grid();

	void SetFile(char * str); // Đọc các object từ file
	void ReloadGrid();


	BaseObject * GetNewObject(int type, float x, float y, int w, int h, int Model);
	void Insert(int id, int type, int direction, float x, float y, int w, int h, int Model); //Thêm object vào grid
	void GetListObject(vector<BaseObject*>& ListObj, Camera * camera);

};

#endif