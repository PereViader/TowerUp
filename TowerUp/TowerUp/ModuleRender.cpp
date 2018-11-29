#include "stdafx.h"
#include "ModuleRender.h"
#include "Game.h"


ModuleRender::ModuleRender()
{
}


ModuleRender::~ModuleRender()
{
	_window->close();
}

bool ModuleRender::Init()
{
	_window.reset(new sf::RenderWindow(sf::VideoMode(720, 1280), "TowerUp", sf::Style::Close | sf::Style::Titlebar));
	_window->setFramerateLimit(60);
	//_view.reset(new sf::View(_window->getDefaultView()));
	//_window->setView(*_view);

	return true;
}

void ModuleRender::Draw(const sf::Drawable & drawable)
{
	_renderQueue.push_back(&drawable);
}

UpdateStatus ModuleRender::PreUpdate()
{
	if (!_window->isOpen())
	{
		return UpdateStatus::Error;
	}

	_window->clear();
	return UpdateStatus::Continue;
}

UpdateStatus ModuleRender::Update()
{
	/*sf::Vector2f movement;
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

	game->Camera().Move(movement);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		game->Camera().Reset();
	}*/

	return UpdateStatus::Continue;
}

UpdateStatus ModuleRender::PostUpdate()
{
	for (auto drawable : _renderQueue)
	{
		_window->draw(*drawable);
	}

	_renderQueue.clear();
	_window->display();
	return UpdateStatus::Continue;
}

sf::RenderWindow & ModuleRender::GetWindow() const
{
	return *_window;
}
