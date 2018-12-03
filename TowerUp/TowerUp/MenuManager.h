#pragma once
#include "Entity.h"

#include <SFML/Audio.hpp>

class MenuManager :
	public Entity
{
public:
	MenuManager();
	virtual ~MenuManager();

	virtual void Init() override;

private:
	std::shared_ptr <sf::Music> _menuMusic;
};

