#pragma once
#include <chrono>

using namespace std::chrono;

class SynchronisationClock
{
protected:
	milliseconds _initTime;
	bool _isInit = false;
public :
	void Init();
	inline bool IsInit() { return _isInit; }
};
