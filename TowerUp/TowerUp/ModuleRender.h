#pragma once

#include "Module.h"

#include <list>
#include <memory>

#include "SFML\Graphics.hpp"

#include "Entity.h"

class ModuleRender :
	public Module
{
public:
	ModuleRender();
	virtual ~ModuleRender();

	void DrawDebugCircle(const sf::Vector2f& position, float ratius=5.0f);
	void Draw(const sf::Drawable&, EntityType);
	sf::RenderWindow& GetWindow() const;


	virtual bool Init() override;

	virtual UpdateStatus PreUpdate() override;
	virtual UpdateStatus PostUpdate() override;

	sf::View& GetWorldView();
	sf::View& GetUiView();

private:
	std::list<sf::CircleShape> _debugWorldCircleQueue;
	std::list<const sf::Drawable*> _worldRenderQueue;
	std::list<const sf::Drawable*> _uiRenderQueue;

	std::unique_ptr<sf::RenderWindow> _window;
	std::unique_ptr<sf::View> _worldView;
	std::unique_ptr<sf::View> _uiView;
};

