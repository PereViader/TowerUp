#include "stdafx.h"
#include "ModuleCamera.h"

#include "Game.h"

ModuleCamera::ModuleCamera()
{
}


ModuleCamera::~ModuleCamera()
{
}

UpdateStatus ModuleCamera::PostUpdate()
{
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
