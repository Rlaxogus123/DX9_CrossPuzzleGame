#include "DXUT.h"
#include "Include.h"

Tile::Tile()
{
	SetTexture(L"Tile.png");
	state = 0;
	count = false;
	_visible = false;
}

void Tile::Update()
{
	if (!_visible) return;

	// Game //
	if (Game::GetIns()->isWorldClick(GetRect()))
	{
		if (Game::GetIns()->clickState == 1)
			state = 1;
		if (Game::GetIns()->clickState == 2)
			state = 0;
	}
	// Game //

	// GamePlay //
	if (GamePlay::GetIns()->isWorldClick(GetRect()))
	{
		if (GamePlay::GetIns()->clickState == 1)
		{
			if (state != 1)
			{
				state = 1;
				if (count)
				{
					GamePlay::GetIns()->curpose++;
				}
				else
				{
					GamePlay::GetIns()->errorpose++;
				}
			}
		}
		if (GamePlay::GetIns()->clickState == 2)
		{
			if (state == 1)
			{
				if (count)
				{
					GamePlay::GetIns()->curpose--;
				}
				else
				{
					GamePlay::GetIns()->errorpose--;
				}
			}
			state = 2;
		}
		if (GamePlay::GetIns()->clickState == 3)
		{
			if (state == 1)
			{
				if (count)
				{
					GamePlay::GetIns()->curpose--;
				}
				else
				{
					GamePlay::GetIns()->errorpose--;
				}
			}
			state = 0;
		}
	}
	if (GamePlay::GetIns()->gameclear && !count)
	{
		_color.a -= TIME::delta;
	}
	// GamePlay //
	else
	{
		if (state == 0)
		{
			if (_texture->_path == L"TileNo.png") SetTexture(L"Tile.png");
			_color = color(1, 1, 1, 1);
		}
		if (GamePlay::GetIns()->cheat)
		{
			if (count) _color = color(1, 0, 0, 1);
		}
		if (state == 1)
		{
			_color = color(0, 0, 0, 1);
			if (GamePlay::GetIns()->cheat && !count)
			{
				_color = color(1, 0, 1, 1);
			}
		}

		if (state == 2)
		{
			if (_texture->_path == L"Tile.png") SetTexture(L"TileNo.png");
			_color = color(1, 1, 1, 1);
		}
	}
}