#include "stdafx.h"
#include "ModuleTime.h"


ModuleTime::ModuleTime()
{
}


ModuleTime::~ModuleTime()
{
}

UpdateStatus ModuleTime::PreUpdate()
{
	_frameCount += 1;

	_deltaTime = _clock.restart().asSeconds();
	_timeFromStart += _deltaTime;

	return UpdateStatus::Continue;
}

float ModuleTime::GetDeltaTime()
{
	return _deltaTime;
}

float ModuleTime::GetTimeFromStart()
{
	return _timeFromStart;
}

unsigned int ModuleTime::GetFrameCount()
{
	return _frameCount;
}
