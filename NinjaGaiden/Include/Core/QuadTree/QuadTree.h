#pragma once

#include <Core/QuadTree/BoundingBox.h>
#include <vector>

class QuadTree;

struct QuadTreeObject {
  friend class QuadTree;

  QuadTreeObject(const BoundingBox &boundingBox = {},
                 GameObject *pObject = nullptr);
  ~QuadTreeObject();

  BoundingBox Bound;
  GameObject *pObject;

private:
  QuadTree *mQuadTree = nullptr;

  QuadTreeObject(const QuadTreeObject &) = delete;
};

class QuadTree {
  bool mIsLeaf = true;
  unsigned mLevel = 0;
  unsigned mCapacity;
  unsigned mMaxLevel;

  BoundingBox mBoundingBox;

  QuadTree *mpParent = nullptr;
  QuadTree *mpChildren[4] = {nullptr, nullptr, nullptr, nullptr};

  std::vector<QuadTreeObject *> mpObjects;
  std::vector<QuadTreeObject *> mpFoundObjects;

  void Subdivide();
  void DiscardEmptyBuckets();

  inline QuadTree *GetChild(const BoundingBox &boundingBox) const;

public:
  QuadTree(const BoundingBox &boundingBox, unsigned capacity = 10,
           unsigned maxLevel = 10);
  QuadTree(const QuadTree &quadTree);
  QuadTree();

  ~QuadTree();

  bool Insert(QuadTreeObject *obj);
  bool Remove(QuadTreeObject *obj);
  bool Update(QuadTreeObject *obj);

  std::vector<QuadTreeObject *> &
  GetObjectsInBound(const BoundingBox &boundingBox);

  unsigned TotalChildren() const;
  unsigned TotalObjects() const;

  void Clear();
};
