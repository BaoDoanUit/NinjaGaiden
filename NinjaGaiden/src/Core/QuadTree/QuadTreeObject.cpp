#include "Core/QuadTree/QuadTree.h"

QuadTreeObject::QuadTreeObject(const BoundingBox &boundingBox,
                               GameObject *pObject) {
  this->Bound = boundingBox;
  this->pObject = pObject;
}