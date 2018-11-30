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
		case sf::Event::Closed: // We closed the window -> stop the game
			return UpdateStatus::Stop;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Key::F1:
				game->Collision().ToggleCollidableDrawing();
				break;
			case sf::Keyboard::Key::F2:
				game->Camera().ToggleManualCameraControl();
				break;
			default:
				//Not handled
				break;
			}

		default:
			//Not handled
			break;
		}
	}

	return UpdateStatus::Continue;
}
