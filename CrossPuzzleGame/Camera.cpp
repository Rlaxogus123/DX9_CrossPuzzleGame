#include "DXUT.h"
#include "Include.h"

void Camera::CameraInit()
{
	D3DXMatrixOrthoLH(&OM, ScreenWidth, -ScreenHeight, 0, 1);
	D3DXMatrixIdentity(&IM);
	_camSize = 0;
	_camPos = { ScreenWidth / 2, ScreenHeight / 2 };
}

void Camera::CameraUpdate()
{
	VM = D3DXMATRIX{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		-_camPos.x, -_camPos.y,0,1
	};
	D3DXMatrixOrthoLH(&OM, ScreenWidth * _camSize, -ScreenHeight * _camSize, 0, 1);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &OM);
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &IM);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &VM);
}
