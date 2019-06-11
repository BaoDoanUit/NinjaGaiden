#include <Objects/Map/MapBackgroundLayer.h>

#include "../../../../Sprite.h"
#include <Core/ResourceManager.h>
#include <core/Config.h>

using namespace rapidjson;

MapBackgroundLayer::MapBackgroundLayer(const std::string &name,
                                       const std::string &filePath,
                                       const GenericValue<UTF8<>> &data) {
  auto resourceManager = ResourceManager::GetInstance();

  this->mName = name;
  this->mWidth = data["width"].GetInt();
  this->mHeight = data["height"].GetInt();

  this->mTexture = resourceManager->GetTexture(filePath);

  this->mpTiles = new int *[this->mHeight];

  for (int i = 0; i < this->mHeight; i++) {
    this->mpTiles[i] = new int[this->mWidth];
  }

  auto tilesData = data["data"].GetArray();

  int row = 0;
  int column = 0;

  for (SizeType i = 0; i < tilesData.Size(); i++) {
    this->mpTiles[row][column] = tilesData[i].GetInt();

    row++;

    if (row >= this->mHeight) {
      row = 0;
      column++;
    }
  }
}

MapBackgroundLayer::~MapBackgroundLayer() {
  for (int i = 0; i < this->mHeight; i++) {
    SAFE_DELETE_ARRAY(this->mpTiles[i]);
  }

  SAFE_DELETE_ARRAY(this->mpTiles);
}

void MapBackgroundLayer::DrawTile(const BoundingBox &b) {
  D3DXVECTOR3 texturePosition(b.GetX(), b.GetY(), 0);

  int value = b.Data;

  int x = (value - 1) / 12;
  int y = (value - 1) % 12;

  RECT bound{x * 32, y * 32, x + 32, y + 32};

  auto sprite = G_SpriteHandler;

  D3DXVECTOR3 c{0, 0, 0};

  sprite->Draw(this->mTexture, &bound, &c, &texturePosition, WHITE_COLOR);
}