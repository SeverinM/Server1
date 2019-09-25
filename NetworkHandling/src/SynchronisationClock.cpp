#include "SynchronisationClock.h"

void SynchronisationClock::Init()
{
	_isInit = true;
	_initTime = duration_cast<milliseconds> (system_clock::now().time_since_epoch());
}