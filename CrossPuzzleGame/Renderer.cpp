#include "DXUT.h"
#include "Include.h"

bool Renderer::Comp(Node* a, Node* b)
{
	return a->_layer < b->_layer;
}

void Renderer::AddRender(Node* n)
{
	if (find(_rendertarget.begin(), _rendertarget.end(), n) != _rendertarget.end())
		return;
	_rendertarget.push_back(n);
}

void Renderer::DeleteRender(Node* n)
{
	_rendertarget.remove(n);
}

void Renderer::Render()
{
	_rendertarget.sort(Comp);
	for (auto it : _rendertarget)
	{
		it->Draw();
		it->Update();
	}
}
