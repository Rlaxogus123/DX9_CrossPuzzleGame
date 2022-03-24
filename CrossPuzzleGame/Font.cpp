#include "DXUT.h"
#include "Include.h"

Font::Font()
{
	_isUI = false;
	_font = nullptr;
	_color = color(1, 1, 1, 1);
	_position = { 0,0 };
	memset(buff, 0,200);
	D3DXCreateFont(DXUTGetD3D9Device(), 20, 0, FW_NORMAL, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, L"Arial", &_font);
	FontMNG::GetIns()->AddFont(this);
}

Font::~Font()
{
	FontMNG::GetIns()->RemoveFont(this);
}

void Font::SetString(char* _string)
{
	sprintf(buff, _string);
}

void Font::CreateMyfont(float size, float weigth, LPCWSTR _path)
{
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * size, 0, weigth, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, _path, &_font);
}

void Font::Draw()
{
	RECT r;
	if (_isUI)
	{
		r = { (long)_position.x, (long)_position.y, 0, 0 };
	}
	else
	{
		r = { (long)(_position.x - (Camera::GetIns()->_camPos.x - ScreenWidth / 2)) ,
		(long)(_position.y - (Camera::GetIns()->_camPos.y - ScreenHeight / 2)) , 0, 0 };
	}
	
	_font->DrawTextA(nullptr, buff, -1, &r, DT_NOCLIP, _color);
}

void FontMNG::AddFont(Font* f)
{
	_fontlist.push_back(f);
}

void FontMNG::RemoveFont(Font* f)
{
	_fontlist.remove(f);
}

void FontMNG::RenderFont()
{
	for (auto it : _fontlist)
	{
		it->Draw();
	}
}
