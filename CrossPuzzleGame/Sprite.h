#pragma once
class Sprite : public Node
{
public:
	Sprite();
	Sprite(wstring _path);
	~Sprite();

	LPD3DXSPRITE _sprite;
	Texture* _texture;

	void SetTexture(wstring _path);
	void SetTexture(Texture* texture);
	void Draw() override;
	RECT GetRect();

	bool Goto(vec2 target, float speed);
	void LookAt(vec2 target);
	void LookAt(Sprite* target);
	void RotationMove(float speed);
};

