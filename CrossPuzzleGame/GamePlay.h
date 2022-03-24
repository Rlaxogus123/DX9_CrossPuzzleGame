#pragma once

class GamePlay : public Singleton<GamePlay>
{
public:
	Font* size;
	Tile* tile;

	int sizeX;
	int sizeY;
	int clickState;
	int purpose;
	int curpose;
	int errorpose;

	bool gameclear;
	bool cheat;

	vec2 firstpos;
	vec2 curpos;

	Sprite* backEditor;
	Sprite* start;
	bool really;

	vector<Tile*> tilelist;
	vector<Font*> fontlist;

	void CreateTile();
	void DeleteTile();
	void DeleteFont();
	void verticalReadLine();
	void horizontalReadLine();

	bool isClick(RECT r);
	bool isWorldClick(RECT r);

	void InitGamePlay();
	void UpdateGamePlay();
	void OnExitGamePlay();
};

