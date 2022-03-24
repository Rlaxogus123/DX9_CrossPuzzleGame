#pragma once
class Game : public Singleton<Game>
{
public:
	int sizeX;
	int sizeY;
	int clickState;

	Tile* tile;
	Font* size;

	Sprite* createtile;
	Sprite* exporttile;
	Sprite* exportSuccess;
	Sprite* backEditor;
	bool really;

	Sprite* uptileX;
	Sprite* downtileX;
	Sprite* uptileY;
	Sprite* downtileY;
	
	vec2 firstpos;
	vec2 curpos;

	vector<Tile*> tilelist;
	vector<Font*> fontlist;

	void CreateTile();
	void DeleteTile();
	void DeleteFont();
	void verticalReadLine();
	void horizontalReadLine();

	void SafeTileData();

	bool isClick(RECT r);
	bool isWorldClick(RECT r);

	void GameInit();
	void GameUpdate();
	void GameExit();
};

