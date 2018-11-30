#include "stdafx.h"
#include "ModuleCamera.h"

#include "Game.h"

ModuleCamera::ModuleCamera()
{
}


ModuleCamera::~ModuleCamera()
{
}

void ModuleCamera::ManualCameraControl()
{
	sf::Vector2f movement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		movement.y += 0.25f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		movement.y -= 0.25f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		movement.x += 0.25f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		movement.x -= 0.25f;
	}

	Move(movement);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		Reset();
	}
}

UpdateStatus ModuleCamera::PostUpdate()
{
	if (_manualCameraControl)
	{
		ManualCameraControl();
	}

	sf::RenderWindow& window = game->Render().GetWindow();
	sf::View view = window.getView();
	view.move(_movement);
	window.setView(view);

	_movement = sf::Vector2f(0,0);

	return UpdateStatus::Continue;
}

void ModuleCamera::Move(sf::Vector2f movement)
{
	_movement += movement;
}

void ModuleCamera::SetPosition(sf::Vector2f position)
{
	sf::RenderWindow& window = game->Render().GetWindow();
	sf::View view = window.getView();
	view.setCenter(position);
	window.setView(view);
}

void ModuleCamera::Reset()
{
	//_trauma = 0;
	_movement = sf::Vector2f(0, 0);
	SetPosition(sf::Vector2f(0, 0));
}

void ModuleCamera::AddTrauma(float amount)
{
	//todo
}

void ModuleCamera::ToggleManualCameraControl()
{
	_manualCameraControl = !_manualCameraControl;
}
