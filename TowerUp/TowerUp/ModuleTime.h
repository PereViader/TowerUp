#pragma once
#include <SFML\System.hpp>

#include "Module.h"

class ModuleTime :
	public Module
{
public:
	ModuleTime();
	~ModuleTime();

	virtual UpdateStatus PreUpdate() override;


	float GetDeltaTime();
	float GetTimeFromStart();
	unsigned int GetFrameCount();

private:
	sf::Clock _clock;
	float _deltaTime = 0.0f;
	float _timeFromStart = 0.0f;
	unsigned int _frameCount = 0;
};

