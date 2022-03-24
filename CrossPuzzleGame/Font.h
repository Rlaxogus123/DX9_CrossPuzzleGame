#pragma once
class Font
{
public:
	Font();
	~Font();

	LPD3DXFONT _font;
	vec2 _position;
	color _color;
	bool _isUI;
	
	char buff[200];

	void SetString(char* _string);
	void CreateMyfont(float size, float weigth, LPCWSTR _path = L"Arial");
	void Draw();
};

class FontMNG : public Singleton<FontMNG>
{
public:
	Font* _font;
	list<Font*> _fontlist;

	void AddFont(Font* f);
	void RemoveFont(Font* f);
	void RenderFont();
};
