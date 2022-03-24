#pragma once
class Camera : public Singleton<Camera>
{
private:
	D3DXMATRIX OM;
	D3DXMATRIX IM;
	D3DXMATRIX VM;
public:
	vec2 _camPos;
	float _camSize;

	void CameraInit();
	void CameraUpdate();
};

