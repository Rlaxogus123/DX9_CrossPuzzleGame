#pragma once
template <class T>
class Singleton
{
private:
	static T* _ins;
public:
	static T* GetIns()
	{
		if (_ins == nullptr)
			_ins = new T();
		return _ins;
	}
};

template <class T> T* Singleton<T>::_ins = nullptr;

class TIME
{
public:
	static int score;
	static float delta;
	static float scale;
};

