#pragma once
class Node
{
public:
	Node();
	~Node() {};

	vec2 _position;
	vec2 _scale;
	vec2 _pivot;
	vec2 _u;

	float _rotation;
	float _r;

	int _isUI;
	int _layer;

	bool _visible;

	color _color;
	RECT _imgRect;

	virtual void Draw() {};
	virtual void Update() {};
	D3DXMATRIX GetMatrix();
};

