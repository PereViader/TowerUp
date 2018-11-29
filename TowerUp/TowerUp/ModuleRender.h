#pragma once

#include "Module.h"

#include <list>
#include <memory>

#include "SFML\Graphics.hpp"

class ModuleRender :
	public Module
{
public:
	ModuleRender();
	virtual ~ModuleRender();

	void Draw(const sf::Drawable&);
	sf::RenderWindow& GetWindow() const;


	virtual bool Init() override;

	virtual UpdateStatus PreUpdate() override;
	virtual UpdateStatus Update() override;
	virtual UpdateStatus PostUpdate() override;


private:
	std::list<const sf::Drawable*> _renderQueue;
	std::unique_ptr<sf::RenderWindow> _window;
	std::unique_ptr<sf::View> _view;
};

