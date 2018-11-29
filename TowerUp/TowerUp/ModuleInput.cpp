#include "stdafx.h"
#include "ModuleInput.h"

#include "SFML\Graphics.hpp"
#include "Game.h"

ModuleInput::ModuleInput()
{
}


ModuleInput::~ModuleInput()
{
}

UpdateStatus ModuleInput::PreUpdate()
{
	sf::Event event;
	sf::RenderWindow& window = game->Render().GetWindow();
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			return UpdateStatus::Stop;
		default:
			//Not precessed
			break;
		}
	}

	return UpdateStatus::Continue;
}
