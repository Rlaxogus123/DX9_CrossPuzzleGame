#pragma once
class Texture 
{
public:
	D3DXIMAGE_INFO _info;
	LPDIRECT3DTEXTURE9 _texture;
	wstring _path;
};

class TextureMNG : public Singleton<TextureMNG>
{
private:
	list<Texture*> _texturelist;
public:
	Texture* LoadTexture(wstring _path);
};

