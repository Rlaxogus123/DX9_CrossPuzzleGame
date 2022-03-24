#pragma once
class SelectScene : public Scene
{
public:
	bool isClick(RECT r);

	Sprite* playPuzzle;
	Sprite* createPuzzle;

	Sprite* backTitle;

	void Init() override;
	void Update() override;
	void OnExit() override;
};

