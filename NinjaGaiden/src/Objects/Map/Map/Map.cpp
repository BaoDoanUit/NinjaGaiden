#include "Objects/Map/Map.h"

#include "../../../../Sprite.h"
#include <Helpers/FileHelper.h>
#include <rapidjson/document.h>
#include "../../../../TextureManager.h"

using namespace std;
using namespace rapidjson;



Map::Map(const std::string &filePath) {
	string mapData = FileHelper::ReadString(filePath.c_str());
	auto resourceManager = TextureManager::GetInstance();

	Document document;

	document.Parse(mapData.c_str());

	this->mWidth = document["width"].GetInt();
	this->mHeight = document["height"].GetInt();

	auto data = document["background"].GetArray();


	for (int x = 0; x < this->mHeight; x++) {
		for (int y = 0; y < this->mWidth; y++) {
			TileMap[x][y] = data[y][x].GetInt() - 1;
		}
	}
	GTTile = TextureManager::GetInstance()->GetTexture(eType::MAP3);
	ScreenColumn = (G_ScreenWidth) / GTTile->FrameWidth + 1;
	ScreenRow = (G_ScreenHeight) / GTTile->FrameHeight + 1;
	//G_MapWidth = (GTTile->FrameHeight)*(ColumnMatrix*(State > 0) + (State == 0));//dùng ở hàm SceneMain.cpp
																				 //G_MapHeight = (GTTile->FrameHeight)*(RowMatrix*(State > 0) + (State == 0));
	GSTile = new Sprite(GTTile, 0);
	/*

	#pragma region Quadtree

		BoundingBox quadTreeBound;

		quadTreeBound.Position.x = 0;
		quadTreeBound.Position.y = 0;
		quadTreeBound.Width = this->mWidth * TILE_WIDTH;
		quadTreeBound.Height = this->mHeight * TILE_HEIGHT;

		this->mpQuadTree = new QuadTree(quadTreeBound);
		GTTile = TextureManager::GetInstance()->GetTexture(eType::MAP3);
	#pragma endregion

	#pragma region Load background

		for (int x = 0; x < this->mWidth; x++) {
			vector<int> col(this->mHeight);

			for (int y = 0; y < this->mHeight; y++) {
				col[y] = data[x][y].GetInt();

				BoundingBox bound;

				bound.Position.x = x * TILE_WIDTH;
				bound.Position.y = y * TILE_HEIGHT;
				bound.Width = TILE_WIDTH;
				bound.Height = TILE_HEIGHT;

				MapBackgroundTile *pTile = new MapBackgroundTile(bound, col[y]);

				this->mBackgroundTiles.push_back(pTile);

				this->mpQuadTree->Insert(new QuadTreeObject(bound, pTile));
			}

			this->mBackgroundData.push_back(col);
		}

		this->mBackgroundTexture = resourceManager->GetTexture(eType::MAP3)->texture;


	#pragma endregion
	*/
}

Map::~Map() {
	SAFE_DELETE(this->mpQuadTree);

	for (auto &it : this->mBackgroundTiles) {
		SAFE_DELETE(it);
	}
}

void Map::Render(Camera* camera) {
	G_SpriteHandler;

	BoundingBox cameraBound{ -camera->viewport.x ,0 ,900 , 400 };

	for (int x = 0; x < this->mWidth; x++) {
		for (int y = 0; y < this->mHeight; y++) {
			int value = this->mBackgroundData[x][y];

			if (value > -1) {
				value--;

				D3DXVECTOR3 texturePosition{ 0, 0, 0 };

				texturePosition.x = x * TILE_WIDTH;
				texturePosition.y = y * TILE_HEIGHT;

				BoundingBox objBound(texturePosition.x, texturePosition.y, TILE_WIDTH,
					TILE_HEIGHT);

				if (cameraBound.Intersects(objBound)) {
					RECT bound{ TILE_WIDTH, TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

					bound.left *= value % MAP_BACKGROUND_TILE_COUNT;
					bound.top *= value / MAP_BACKGROUND_TILE_COUNT;
					bound.right += bound.left;
					bound.bottom += bound.top;

					G_SpriteHandler->Draw(this->mBackgroundTexture, &bound, nullptr,
						&texturePosition, WHITE_COLOR);
				}
			}
		}
	}

}

void Map::Render2(Camera* camera) {

	row = int(camera->viewport.y) / GTTile->FrameHeight;
	column = int(camera->viewport.x) / GTTile->FrameWidth;

	x = -(int(camera->viewport.x) % GTTile->FrameWidth);
	y = (int(camera->viewport.y) % GTTile->FrameHeight);

	for (int i = 0; i < ScreenRow; i++)
	{
		for (int j = 0; j < ScreenColumn; j++)
		{
			if (!(this->mHeight - row + i < 0 || this->mHeight - row + i >= this->mHeight))
			{
				GSTile->SelectIndex(TileMap[this->mHeight - row + i][column + j]);
				GSTile->DrawFromTL(x, y);
				x = x + GTTile->FrameWidth;
			}
		}

		y = y + GTTile->FrameHeight;
		x = -int(camera->viewport.x) % GTTile->FrameHeight;
	}
}