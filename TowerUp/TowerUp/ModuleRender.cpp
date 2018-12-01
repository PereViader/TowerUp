#include "stdafx.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "Game.h"


ModuleRender::ModuleRender() :
	_window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TowerUp", sf::Style::Close | sf::Style::Titlebar)),
	_worldView(new sf::View(_window->getView())),
	_uiView(new sf::View(_window->getView()))
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

void ModuleRender::Draw(const sf::Drawable & drawable, EntityType drawableType)
{
	if (drawableType == EntityType::World)
	{
		_worldRenderQueue.push_back(&drawable);
	}
	else // drawableType == DrawableType::UI
	{
		_uiRenderQueue.push_back(&drawable);
	}
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
	_window->setView(*_worldView);
	for (auto drawable : _worldRenderQueue)
	{
		_window->draw(*drawable);
	}
	_worldRenderQueue.clear();

	_window->setView(*_uiView);
	for (auto drawable : _uiRenderQueue)
	{
		_window->draw(*drawable);
	}
	_uiRenderQueue.clear();

	_window->setView(*_worldView);


	_window->display();
	return UpdateStatus::Continue;
}

sf::View & ModuleRender::GetUiView()
{
	return *_uiView;
}

sf::View & ModuleRender::GetWorldView()
{
	return *_worldView;
}

sf::RenderWindow & ModuleRender::GetWindow() const
{
	return *_window;
}
