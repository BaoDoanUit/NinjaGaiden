#pragma once

#include "Core/GameObject.h"
#include "../../../Global.h"

#include <string>

#include <Core/QuadTree/BoundingBox.h>
#include <rapidjson/document.h>
#include <vector>

class MapBackgroundTile : public GameObject {
public:
  D3DXVECTOR2 Position{0, 0};
};

class MapBackgroundLayer : public GameObject {
  std::string mName;

  int mWidth;
  int mHeight;

  int **mpTiles;

  LPDIRECT3DTEXTURE9 mTexture;

public:
  MapBackgroundLayer(const std::string &name, const std::string &filePath,
                     const rapidjson::GenericValue<rapidjson::UTF8<>> &data);
  ~MapBackgroundLayer();

  int GetWidth() const { return this->mWidth; }
  int GetHeight() const { return this->mHeight; }

  int **GetTilesData() const { return this->mpTiles; }

  int GetTileValue(int row, int column) const {
    return this->mpTiles[row][column];
  }

  void DrawTile(const BoundingBox &b);
};
