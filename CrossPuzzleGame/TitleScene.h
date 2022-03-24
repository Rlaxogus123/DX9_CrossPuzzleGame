#pragma once
class TitleScene : public Scene
{
public:
	Sprite* title;
	Sprite* start;
	Sprite* end;
	Sprite* background;

	bool isClick(RECT r);

	void Init() override;
	void Update() override;
	void OnExit() override;
};

