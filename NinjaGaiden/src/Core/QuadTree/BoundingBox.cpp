#include <Core/QuadTree/BoundingBox.h>

BoundingBox::BoundingBox() { this->Position = {0, 0}; }

BoundingBox::BoundingBox(float x, float y, float width, float height) {
  this->Position.x = x;
  this->Position.y = y;
  this->Width = width;
  this->Height = height;
}

BoundingBox::BoundingBox(const BoundingBox &boundingBox) {
  this->Position = boundingBox.Position;
  this->Width = boundingBox.Width;
  this->Height = boundingBox.Height;
  this->Data = boundingBox.Data;
}

D3DXVECTOR2 BoundingBox::GetPosition() const { return this->Position; }

float BoundingBox::GetLeft() const { return this->Position.x; }

float BoundingBox::GetTop() const { return this->Position.y; }

float BoundingBox::GetRight() const { return this->Position.x + this->Width; }

float BoundingBox::GetBottom() const { return this->Position.y + this->Height; }

float BoundingBox::GetWidth() const { return this->Width; }

float BoundingBox::GetHeight() const { return this->Height; }

float BoundingBox::GetX() const { return this->Position.x; }

float BoundingBox::GetY() const { return this->Position.y; }

bool BoundingBox::Contains(const BoundingBox &boundingBox) const {
  if (this->Position.x > boundingBox.Position.x) {
    return false;
  }

  if (this->Position.y > boundingBox.Position.y) {
    return false;
  }

  if (this->Position.x + this->Width <
      boundingBox.Position.x + boundingBox.Width) {
    return false;
  }

  if (this->Position.y + this->Height <
      boundingBox.Position.y + boundingBox.Height) {
    return false;
  }

  return true;
}

bool BoundingBox::Intersects(const BoundingBox &boundingBox) const{
  if (this->Position.x > boundingBox.Position.x + boundingBox.Width) {
    return false;
  }
  if (this->Position.x + this->Width < boundingBox.Position.x) {
    return false;
  }

  if (this->Position.y > boundingBox.Position.y + boundingBox.Height) {
    return false;
  }

  if (this->Position.y + this->Height < boundingBox.Position.y) {
    return false;
  }

  return true;
}