#pragma once
class Sound : public Singleton<Sound>
{
public:
	void PlayEf(wstring path);
	void PlayBg(wstring path);
};

