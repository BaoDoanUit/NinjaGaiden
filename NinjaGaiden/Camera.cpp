#include "Camera.h"

Camera::Camera(int x, int State)
{
	viewport.x = x;
	if (State == 2)
		viewport.y = G_ScreenHeight + 416;
	else
		if (State == 3)
			viewport.y = G_ScreenHeight + 1152;
		else
			viewport.y = G_ScreenHeight;
}
void Camera::SetSizeMap(int _min, int _max)
{
	_maxSize = _max;
	_minSize = _min;
}

D3DXVECTOR2 Camera::Transform(int x, int y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}

D3DXVECTOR3 Camera::CenterSprite(int x, int y)
{
	D3DXVECTOR3 pCenter = D3DXVECTOR3(x / 2, y / 2, 0);
	return pCenter;
}

void Camera::UpdateCamerax(int x)
{
	viewport.x = viewport.x + x;
	//Cái này chỉ dùng để test thử khi sang trái phải camera khi nào gắn ninjaGaiden thì bỏ hàm này sử dụng hàm UpdateCamera bên dưới(Tiền update)
	if (viewport.x + G_ScreenWidth > _maxSize)
		viewport.x = _maxSize - G_ScreenWidth;
	if (viewport.x < _minSize)
		viewport.x = _minSize;
}

void Camera::UpdateCameray(int x)
{
	viewport.y = viewport.y + x;
}
void Camera::UpdateCamera(int &w, int &h)
{

}

void Camera::SetVCam(float vcamX, float vcamY) {
	_VCameraX = vcamX;
}
void Camera::UpdateCamera() {
	if ((_FolowPosX >= G_ScreenWidth / 2 + viewport.x && _VCameraX > 0) || (_FolowPosX <= viewport.x + G_ScreenWidth / 2 && _VCameraX < 0))
	{
		viewport.x += _VCameraX;
	}
	if (viewport.x + G_ScreenWidth > _maxSize)
		viewport.x = _maxSize - G_ScreenWidth;
	if (viewport.x < _minSize) viewport.x = _minSize;
}

void Camera::SetFolowPos(float x, float y)
{
	_FolowPosX = x;
	_FolowPosY = y;
}

float Camera::GetXCam()
{
	return viewport.x;
}

float Camera::GetYCam()
{
	return viewport.y;
}

D3DXVECTOR2 Camera::TransformObject(int xWorld, int yWorld)
{
	return D3DXVECTOR2(xWorld - viewport.x,  viewport.y - yWorld);
}



//D3DXVECTOR2 Camera::Transform(int xWorld, int yWorld)
//{
//	return D3DXVECTOR2(xWorld - viewport.x, yWorld - 0);
//}