#pragma once

#define MAP_BACKGROUND_TILE_COUNT 5

#include <string>

#include "Core/GameObject.h"
#include <Core/QuadTree/QuadTree.h>
#include <d3d9.h>
#include "../../../Camera.h"
#include "../../../Sprite.h"

class MapBackgroundTile : public GameObject {
public:
	
	MapBackgroundTile(BoundingBox bound, int value = -1)
		: Bound(bound), Value(value) {}
	~MapBackgroundTile() {};

	BoundingBox Bound;
	int Value = -1;
};

/*===============================================================*/

class Map : public GameObject {
	int TileMap[500][176];
	Texture * GTTile;
	unsigned mWidth = 0;
	unsigned mHeight = 0;

	std::vector<std::vector<int>> mBackgroundData;

	LPDIRECT3DTEXTURE9 mBackgroundTexture;

	QuadTree *mpQuadTree;

	std::vector<MapBackgroundTile *> mBackgroundTiles;
	int ScreenColumn;
	int ScreenRow;
	int row, column;
	int x, y;
public:
	Sprite *GSTile;
	Map(const std::string &filePath);
	~Map();

	void Render(Camera * cam);
	void Render2(Camera* cam);
};
