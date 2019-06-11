#include "Sprite.h"
#include "Global.h"

Sprite::Sprite()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

Sprite::Sprite(const Sprite &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
}

Sprite::Sprite(Texture* texture, int start, int end, int timeAnimation)
	: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
	SetARGB();
}

Sprite::Sprite(Texture* texture, int timeAnimation)
	: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

Sprite::Sprite(Texture* texture)
	: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

Sprite::~Sprite()
{
	if (_texture != NULL)
		delete _texture;
}
void Sprite::SetARGB(int r, int g, int b, int a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

void Sprite::Next()
{
	_index++;
	if (_index > _end)
		_index = _start;
}

void Sprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void Sprite::SelectIndex(int index)
{
	_index = index;
}

void Sprite::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		this->Next();
	}
}

void Sprite::DrawFromCenter(int X, int Y)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

													 //D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(R, G, B) //color
	);
}

void Sprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	this->DrawFromCenter(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void Sprite::DrawFlipY(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	this->DrawFromCenter(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void Sprite::DrawRect(int X, int Y, RECT SrcRect)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	G_SpriteHandler->Draw(
		_texture->texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(R, G, B) //color
	);
}

void Sprite::DrawIndex(int index, int X, int Y)
{
	RECT srect;

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(R, G, B) //color
	);
}

int Sprite::GetIndex()
{
	return _index;
}


void Sprite::DrawFromTL(int X, int Y)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameWidth;// + 1;

													 //D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X;
	position.y = Y;
	G_SpriteHandler->Draw(
		_texture->texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(R, G, B) //color
	);
}


