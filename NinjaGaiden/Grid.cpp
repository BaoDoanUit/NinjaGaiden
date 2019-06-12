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


	int id, type, direction, w, h, model, n, borderLeft, borderRight;
	float x, y;


	ifstream file;
	file.open(filepath, ios::in);
	file >> n;
	for (int i = 0; i < n; i++)
	{
		file >> id >> type >> direction >> x >> y >> w >> h >> model >> borderLeft >> borderRight;
		Insert(id, type, direction, x, y, w, h, model, borderLeft, borderRight);
	}
	file.close();
}

BaseObject * Grid::GetNewObject(int type, float x, float y, int w, int h, int Model, int borderLeft, int borderRight)
{     
	switch (type)
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
		return new Enemy1(x, y, w, h);
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

void Grid::Insert(int id, int type, int direction, float x, float y, int w, int h, int Model, int borderLeft, int borderRight)
{
	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);
	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + w) / GRID_CELL_WIDTH);

	BaseObject * obj = GetNewObject(type, x, y, w, h, Model, borderLeft, borderRight);
	if (obj == NULL)
		return;

	obj->SetId(id);
	obj->SetTrend(direction);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);
}