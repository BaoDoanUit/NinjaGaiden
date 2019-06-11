#include "Texture.h"
int Texture::GetFrameWidth(){
	return FrameWidth ;
}

int Texture::GetFrameHeight()
{
	return FrameHeight;
}

int Texture::GetColumn()
{
	return Cols;
}

int Texture::GetRow()
{
	return Rows;
}


Texture::Texture(char* _fileName, int cols, int rows, int count, int R, int B, int G)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	FileName = _fileName;
	this->Load(R,B,G);
}

Texture::Texture(const Texture &ctexture)
{
	this->FileName = ctexture.FileName;
	this->Size = ctexture.Size;
	this->Cols = ctexture.Cols;
	this->Rows = ctexture.Rows;
	this->Count = ctexture.Count;
	this->FrameHeight = ctexture.FrameHeight;
	this->FrameWidth = ctexture.FrameWidth;
	this->Load();
}

Texture::~Texture()
{
	if (this->texture != NULL)
		this->texture->Release();
}

void Texture::Draw(int x, int y)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(texture, &Size, NULL, &position, 0xFFFFFFFF);
}

void Texture::Load(int R, int B, int G)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(FileName, &info);

	if (result != D3D_OK)
	{
		GLMessage("Can not load texture");
		GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		OutputDebugString(FileName);
		return;
	}

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	result = D3DXCreateTextureFromFileEx(
		G_Device,
		FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, B, G), //color
		//D3DCOLOR_XRGB(255, 163, 177), //color
		&info,
		NULL,
		&texture
	);

	if (result != D3D_OK)
	{
		GLMessage("Can not load texture");
		GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);
		return;
	}
}