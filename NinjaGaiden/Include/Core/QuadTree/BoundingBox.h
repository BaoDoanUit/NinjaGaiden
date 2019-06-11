#pragma once

#include "../../../Global.h"
#include <Core/GameObject.h>

class BoundingBox {
public:
  D3DXVECTOR2 Position;
  float Width;
  float Height;
  int Data;

  BoundingBox();
  BoundingBox(float x, float y, float width, float height);
  BoundingBox(const BoundingBox &boundingBox);

  D3DXVECTOR2 GetPosition() const;

  float GetLeft() const;
  float GetTop() const;
  float GetRight() const;
  float GetBottom() const;

  float GetWidth() const;
  float GetHeight() const;

  float GetX() const;
  float GetY() const;

  bool Contains(const BoundingBox &boundingBox) const;
  bool Intersects(const BoundingBox &boundingBox) const;
};
