#include "DXUT.h"
#include "Include.h"

Sprite::Sprite()
{
	_sprite = nullptr;
	_texture = nullptr;
	D3DXCreateSprite(DXUTGetD3D9Device(), &_sprite);
}

Sprite::Sprite(wstring _path)
{
	_sprite = nullptr;
	_texture = nullptr;
	D3DXCreateSprite(DXUTGetD3D9Device(), &_sprite);
	SetTexture(_path);
}

Sprite::~Sprite()
{
	Renderer::GetIns()->DeleteRender(this);
}

void Sprite::SetTexture(wstring _path)
{
	_texture = TextureMNG::GetIns()->LoadTexture(_path);
	SetRect(&_imgRect, 0, 0, _texture->_info.Width, _texture->_info.Height);
	Renderer::GetIns()->AddRender(this);
}

void Sprite::SetTexture(Texture* texture)
{
	_texture = texture;
	SetRect(&_imgRect, 0, 0, _texture->_info.Width, _texture->_info.Height);
	Renderer::GetIns()->AddRender(this);
}

void Sprite::Draw()
{
	if (!_visible) return;
	if (_texture == nullptr) return;

	_isUI ? _sprite->Begin(D3DXSPRITE_ALPHABLEND) : _sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	_sprite->SetTransform(&GetMatrix());
	vec3 center = { _pivot.x * _texture->_info.Width, _pivot.y * _texture->_info.Height , 0 };
	_sprite->Draw(_texture->_texture, &_imgRect, &center, nullptr, _color);
	_sprite->End();
}

RECT Sprite::GetRect()
{
	RECT r;

	r.right = _position.x + ((_texture->_info.Width / 2) * fabs(_scale.x));
	r.left = _position.x - ((_texture->_info.Width / 2) * fabs(_scale.x));
	r.top = _position.y - ((_texture->_info.Height / 2) * _scale.y);
	r.bottom = _position.y + ((_texture->_info.Height / 2) * _scale.y);

	return r;
}

bool Sprite::Goto(vec2 target, float speed)
{
	_u = target - _position;
	float size = sqrt(_u.x * _u.x + _u.y * _u.y);
	if (size < 10)
		return true;
	_u.x /= size;
	_u.y /= size;

	_position += _u * speed * TIME::delta;
	return false;
}

void Sprite::LookAt(vec2 target)
{
	_u = target - _position;
	_rotation = atan2(_u.y, _u.x);
}

void Sprite::LookAt(Sprite* target)
{
	_u = target->_position - _position;
	_rotation = atan2(_u.y, _u.x);
}

void Sprite::RotationMove(float speed)
{
	_u = vec2(speed * cosf(_rotation), speed * sinf(_rotation));
	_position += _u * TIME::delta;
}
