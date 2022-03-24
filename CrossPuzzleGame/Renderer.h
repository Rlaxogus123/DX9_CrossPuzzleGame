#pragma once
class Renderer : public Singleton<Renderer>
{
private:
	list<Node*> _rendertarget;
	static bool Comp(Node* a, Node* b);
public:
	void AddRender(Node* n);
	void DeleteRender(Node* n);
	void Render();
};

