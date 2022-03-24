#include "DXUT.h"
#include "Include.h"

Texture* TextureMNG::LoadTexture(wstring _path)
{
	for (auto it : _texturelist)
	{
		if (it->_path == _path)
		{
			return it;
		}
	}

	auto route = L"res/" + _path;
	auto texture = new Texture();
	texture->_path = _path;

	auto isFail = D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), route.c_str(), -2, -2, 1, 0, D3DFORMAT::D3DFMT_A8B8G8R8, D3DPOOL::D3DPOOL_MANAGED
		, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &texture->_info, nullptr, &texture->_texture);

	if (FAILED(isFail))
	{
		wcout << "FAIL!!" << route.c_str() << endl;
		delete texture;
		return nullptr;
	}
	else
	{
		wcout << "LOAD!!" << route.c_str() << endl;
		_texturelist.push_back(texture);
		return texture;
	}
}
