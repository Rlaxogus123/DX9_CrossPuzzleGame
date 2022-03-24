#include "DXUT.h"
#include "Include.h"

void Director::DirectorInit()
{
	cur = nullptr;
	ClickNum = 0;
	Camera::GetIns()->CameraInit();
}

void Director::DirectorUpdate()
{
	if (cur)
		cur->Update();
	Renderer::GetIns()->Render();
	FontMNG::GetIns()->RenderFont();
	Camera::GetIns()->CameraUpdate();

	if (ClickNum == 1) ClickNum++;
	if (ClickNum == 3) ClickNum = 0;

	if (rClickNum == 1) rClickNum++;
	if (rClickNum == 3) rClickNum = 0;

	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);
}

void Director::ChangeScene(Scene* s)
{
	if (cur)
		cur->OnExit();
	cur = s;
	cur->Init();
}

bool Director::MouseDown()
{
	if (ClickNum == 1)
		return true;
	return false;
}

bool Director::Mouse()
{
	if (ClickNum == 2)
		return true;
	return false;
}

bool Director::MouseUp()
{
	if (ClickNum == 3)
		return true;
	return false;
}

bool Director::rMouseDown()
{
	if (rClickNum == 1)
		return true;
	return false;
}

bool Director::rMouse()
{
	if (rClickNum == 2)
		return true;
	return false;
}

bool Director::rMouseUp()
{
	if (rClickNum == 3)
		return true;
	return false;
}
