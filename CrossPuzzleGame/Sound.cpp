#include "DXUT.h"
#include "Include.h"

static int staticCount = 0;

void Sound::PlayEf(wstring path)
{
	sndPlaySound(path.c_str(), SND_ASYNC);
}

void Sound::PlayBg(wstring path)
{
	auto route = L"open " + path + L" type mpegvideo alias " + to_wstring(staticCount);
	mciSendString(route.c_str(), NULL, NULL, NULL);
	route = L"play " + to_wstring(staticCount);
	mciSendString(route.c_str(), NULL, NULL, NULL);
	staticCount++;
}
