#include "stdafx.h"
#include "ModuleCamera.h"

#include "Game.h"
#include "Globals.h"
#include "easylogging++.h"

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
		movement.y += 1.f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		movement.y -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		movement.x += 1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		movement.x -= 1.f;
	}

	Move(movement * DEBUG_CAMERA_SPEED * game->Time().GetDeltaTime());
}

UpdateStatus ModuleCamera::PostUpdate()
{
	if (_manualCameraControl)
	{
		ManualCameraControl();
	}

	game->Render().GetWorldView().move(_movement);

	_movement = sf::Vector2f(0,0);

	return UpdateStatus::Continue;
}

void ModuleCamera::OnPreSceneChange()
{
	Reset();
}

void ModuleCamera::Move(sf::Vector2f movement)
{
	_movement += movement;
}

void ModuleCamera::SetPosition(sf::Vector2f position)
{
	if (!_manualCameraControl)
	{
		game->Render().GetWorldView().setCenter(position);
	}
}

void ModuleCamera::Reset()
{
	_movement = sf::Vector2f(0, 0);
	SetPosition(sf::Vector2f(0, 0));
}

void ModuleCamera::ToggleManualCameraControl()
{
	_manualCameraControl = !_manualCameraControl;
	LOG(INFO) << "Debug Camera Control" << std::to_string(_manualCameraControl);
}

sf::Vector2f ModuleCamera::MouseToWorldPosition() const
{
	return ScreenToWorldPosition(sf::Mouse::getPosition(game->Render().GetWindow()));
}

sf::Vector2f ModuleCamera::ScreenToWorldPosition(const sf::Vector2i& screenPos) const
{
	return game->Render().GetWindow().mapPixelToCoords(screenPos, game->Render().GetWorldView());
}
