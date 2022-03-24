#include "DXUT.h"
#include "Include.h"

Node::Node()
{
	_position = {0,0};
	_scale = {1,1};
	_pivot = {0.5,0.5};
	_u = {0,0};

	_rotation = 0;
	_r = 0;

	_isUI = false;
	_layer = 0;

	_visible = true;

	_color = color(1,1,1,1);
}

D3DXMATRIX Node::GetMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTransformation2D(&m, nullptr, 0, &_scale, nullptr, _rotation, &_position);
	return m;
}
