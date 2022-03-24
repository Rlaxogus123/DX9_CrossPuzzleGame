#pragma once
class Director : public Singleton<Director>
{
public:
	Scene* cur;
	POINT p;
	void DirectorInit();
	void DirectorUpdate();
	void ChangeScene(Scene* s);

	int ClickNum;
	int rClickNum;

	bool MouseDown();
	bool Mouse();
	bool MouseUp();

	bool rMouseDown();
	bool rMouse();
	bool rMouseUp();

	vec2 GetMousePos() { return vec2((float)p.x, (float)p.y); };
};

