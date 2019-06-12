#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}
}

void Grid::SetFile(char * str)
{
	filepath = str;
}

void Grid::ReloadGrid()
{
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}


	int id, typeObject, direction, w, h, typeItem, n, borderLeft, borderRight;
	float x, y;


	ifstream file;
	file.open(filepath, ios::in);
	file >> n;
	for (int i = 0; i < n; i++)
	{
		file >> id >> typeObject >> direction >> x >> y >> w >> h >> typeItem >> borderLeft >> borderRight;
		Insert(id, typeObject, direction, x, y, w, h, typeItem, borderLeft, borderRight);
	}
	file.close();
}



BaseObject * Grid::GetNewObject(int typeObject, float x, float y, int w, int h, int borderLeft, int borderRight)
{     
	switch (typeObject)
	{
	case eType::BEE:
		return new Bee(x, y, w, h);
		break;
	case eType::BIRD:
		return new Bird(x, y, w, h);
		break;
	case eType::DOG:
		return new Dog(x, y, w, h);
		break;
	case eType::EAGLE:
		return new Eagle(x, y, w, h);
		break;
	case eType::ENEMY1:
		return new Enemy1(x, y, w, h,borderLeft,borderRight);
		break;
	case eType::ENEMY2:
		return new Enemy2(x, y, w, h);
		break;
	case eType::SITGUN:
		return new SitGun(x, y, w, h);
		break;
	case eType::STANDSOLIDER:
		return new StandSolider(x, y, w, h);
		break;
	case eType::GROUND:
		return new Ground(x, y, w, h);
		break;
	default:
		break;
	}
	return NULL;
}

void Grid::GetListObject(vector<BaseObject*>& ListObj, Camera * camera)
{
	unordered_map<int, BaseObject*> mapObject;
 	int bottom = (int)((GAME_HEIGHT - 1) / GRID_CELL_HEIGHT);
	int top = (int)(1 / GRID_CELL_HEIGHT);

	int left = (int)((camera->GetXCam() + 1) / GRID_CELL_WIDTH);
	int right = (int)((camera->GetXCam() + G_ScreenWidth - 1) / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->GetHealth() > 0) // còn tồn tại
				{
					if (mapObject.find(cells[i][j].at(k)->GetId()) == mapObject.end()) // ko tìm thấy
						mapObject[cells[i][j].at(k)->GetId()] = cells[i][j].at(k);
				}
				else
				{
						//cells[i][j].erase(cells[i][j].begin() + k); // xóa luôn
				}

			}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}

void Grid::Insert(int id, int typeObject, int direction, float x, float y, int w, int h, int typeItem, int borderLeft, int borderRight)
{
	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);
	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + w) / GRID_CELL_WIDTH);

	BaseObject * obj = GetNewObject(typeObject, x, y, w, h, borderLeft, borderRight);
	Item* item = GetNewItem(typeItem, x, y);
	if (obj == NULL)
		return;

	obj->SetId(id);
	obj->SetTrend(direction);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
		{
			
			cells[i][j].push_back(obj);
			if (item != NULL) {
				cells[i][i].push_back(item);
			}
			

		}
			
}


Item* Grid::GetNewItem(int typeItem, int x, int y)
{
	switch (typeItem)
	{

	}
	return NULL;
}