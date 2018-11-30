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
