#pragma once
#include "Module.h"
#include <SFML\Graphics.hpp>

class ModuleCamera :
	public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	virtual UpdateStatus PostUpdate() override;
	virtual void OnPreSceneChange() override;

	void Move(sf::Vector2f movement);
	void SetPosition(sf::Vector2f position);
	void Reset();
	void AddTrauma(float amount);

	void ToggleManualCameraControl();

private:
	void ManualCameraControl();


private:
	//float _trauma;

	sf::Vector2f _movement;
	bool _manualCameraControl = false;
};

