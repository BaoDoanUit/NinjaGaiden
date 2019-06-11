#include <Core/QuadTree/QuadTree.h>

using namespace std;

QuadTreeObject::~QuadTreeObject() { SAFE_DELETE(this->pObject); }

QuadTree::QuadTree(const BoundingBox &boundingBox, unsigned capacity,
                   unsigned maxLevel) {
  this->mBoundingBox = boundingBox;
  this->mCapacity = capacity;
  this->mMaxLevel = maxLevel;

  this->mpObjects.reserve(capacity);
  this->mpFoundObjects.reserve(capacity);
}

QuadTree::QuadTree(const QuadTree &quadTree)
    : QuadTree(quadTree.mBoundingBox, quadTree.mCapacity, quadTree.mMaxLevel) {}

QuadTree::QuadTree() {}

QuadTree::~QuadTree() {
  this->Clear();

  SAFE_DELETE(this->mpChildren[0]);
  SAFE_DELETE(this->mpChildren[1]);
  SAFE_DELETE(this->mpChildren[2]);
  SAFE_DELETE(this->mpChildren[3]);
}

bool QuadTree::Insert(QuadTreeObject *obj) {
  if (obj->mQuadTree != nullptr) {
    return false;
  }

  if (!this->mIsLeaf) {
    QuadTree *pChild = this->GetChild(obj->Bound);

    if (pChild) {
      return pChild->Insert(obj);
    }
  }

  this->mpObjects.push_back(obj);

  obj->mQuadTree = this;

  if (this->mIsLeaf && (this->mLevel < this->mMaxLevel) &&
      this->mpObjects.size() >= this->mCapacity) {
    this->Subdivide();

    this->Update(obj);
  }

  return true;
}

bool QuadTree::Remove(QuadTreeObject *obj) {
  if (obj->mQuadTree == nullptr) {
    return false;
  }

  if (obj->mQuadTree != this) {
    return obj->mQuadTree->Remove(obj);
  }

  this->mpObjects.erase(
      std::find(this->mpObjects.begin(), this->mpObjects.end(), obj));

  obj->mQuadTree = nullptr;

  this->DiscardEmptyBuckets();

  return true;
}

bool QuadTree::Update(QuadTreeObject *obj) {
  if (!this->Remove(obj)) {
    return false;
  }

  if (this->mpParent != nullptr && !this->mBoundingBox.Contains(obj->Bound)) {
    return this->mpParent->Insert(obj);
  }

  if (!this->mIsLeaf) {
    QuadTree *pChild = this->GetChild(obj->Bound);

    if (pChild) {
      return pChild->Insert(obj);
    }
  }

  return this->Insert(obj);
}

vector<QuadTreeObject *> &
QuadTree::GetObjectsInBound(const BoundingBox &boundingBox) {
  this->mpFoundObjects.clear();

  for (const auto &obj : this->mpObjects) {
    if (&obj->Bound != &this->mBoundingBox &&
        obj->Bound.Intersects(boundingBox))
      this->mpFoundObjects.push_back(obj);
  }

  if (!this->mIsLeaf) {
    QuadTree *pChild = this->GetChild(boundingBox);

    if (pChild) {
      pChild->GetObjectsInBound(boundingBox);

      this->mpFoundObjects.insert(this->mpFoundObjects.end(),
                                  pChild->mpFoundObjects.begin(),
                                  pChild->mpFoundObjects.end());
    } else
      for (QuadTree *pLeaf : this->mpChildren) {
        if (pLeaf->mBoundingBox.Intersects(boundingBox)) {
          pLeaf->GetObjectsInBound(boundingBox);

          this->mpFoundObjects.insert(this->mpFoundObjects.end(),
                                      pLeaf->mpFoundObjects.begin(),
                                      pLeaf->mpFoundObjects.end());
        }
      }
  }

  return this->mpFoundObjects;
}

unsigned QuadTree::TotalChildren() const {
  unsigned total = 0;

  if (this->mIsLeaf) {
    return total;
  }

  for (QuadTree *pChild : this->mpChildren) {
    total += pChild->TotalChildren();
  }

  return 4 + total;
}

unsigned QuadTree::TotalObjects() const {
  unsigned total = static_cast<unsigned>(this->mpObjects.size());

  if (!this->mIsLeaf) {
    for (QuadTree *pChild : this->mpChildren) {
      total += pChild->TotalObjects();
    }
  }

  return total;
}

void QuadTree::Clear() {
  if (!this->mpObjects.empty()) {
    for (auto &&obj : this->mpObjects) {
      obj->mQuadTree = nullptr;
    }

    this->mpObjects.clear();
  }

  if (!this->mIsLeaf) {
    for (QuadTree *pChild : this->mpChildren) {
      pChild->Clear();

      this->mIsLeaf = true;
    }
  }
}

void QuadTree::Subdivide() {
  const float width = this->mBoundingBox.GetWidth() * 0.5f;
  const float height = this->mBoundingBox.GetHeight() * 0.5f;

  float x = 0;
  float y = 0;

  for (int i = 0; i < 4; i++) {
    switch (i) {
    case 0:
      x = this->mBoundingBox.GetLeft() + width;
      y = this->mBoundingBox.GetTop();
      break; // Top right

    case 1:
      x = this->mBoundingBox.GetLeft();
      y = this->mBoundingBox.GetTop();
      break; // Top left

    case 2:
      x = this->mBoundingBox.GetLeft();
      y = this->mBoundingBox.GetTop() + height;
      break; // Bottom left

    case 3:
      x = this->mBoundingBox.GetLeft() + width;
      y = this->mBoundingBox.GetTop() + height;
      break; // Bottom right
    }

    BoundingBox boundingBox(x, y, width, height);

    this->mpChildren[i] =
        new QuadTree(boundingBox, this->mCapacity, this->mMaxLevel);

    this->mpChildren[i]->mLevel = this->mLevel + 1;
    this->mpChildren[i]->mpParent = this;
  }

  this->mIsLeaf = false;
}

void QuadTree::DiscardEmptyBuckets() {
  if (!this->mpObjects.empty()) {
    return;
  }

  if (!this->mIsLeaf) {
    for (QuadTree *pChild : this->mpChildren) {
      if (!pChild->mIsLeaf || !pChild->mpObjects.empty())
        return;
    }
  }

  this->Clear();

  if (this->mpParent != nullptr) {
    this->mpParent->DiscardEmptyBuckets();
  }
}

QuadTree *QuadTree::GetChild(const BoundingBox &boundingBox) const {
  const bool isLeft = boundingBox.GetRight() < this->mBoundingBox.GetRight();

  const bool isRight = boundingBox.GetX() > this->mBoundingBox.GetRight();

  if (boundingBox.GetBottom() < this->mBoundingBox.GetTop()) {
    if (isLeft)
      return this->mpChildren[1]; // Top left

    if (isRight)
      return this->mpChildren[0]; // Top right
  } else if (boundingBox.GetTop() > this->mBoundingBox.GetTop()) {
    if (isLeft)
      return this->mpChildren[2]; // Bottom left

    if (isRight)
      return this->mpChildren[3]; // Bottom right
  }

  return nullptr;
}