#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

class Texture
{
public:
	char* FileName; //đường dẫn tới file ảnh
	RECT Size;		//độ phân giải ảnh
	LPDIRECT3DTEXTURE9 texture;
	int Cols;		//số cột frame
	int Rows;		//số hàng frame
	int Count;		//tổng số frame
	int FrameWidth;		//width of 1 frame
	int FrameHeight;	//height of 1 frame

	Texture(const Texture &ctexture);
	Texture(char* _fileName, int cols = 1, int rows = 1, int count = 1, int R = 255, int B = 163, int G = 177);
	~Texture();
	//vẽ texture tại vị trí (x, y) trên màn hình
	void Draw(int x, int y);
	int GetFrameWidth();
	int GetFrameHeight();
	int GetColumn();
	int GetRow();
protected:
	void Load(int R = 255, int B = 255, int G = 255);
};

#endif