#pragma once
class Tile : public Sprite
{
public:
	Tile();
	int state;
	bool count;
	int x;
	int y;

	void Update() override;
};
