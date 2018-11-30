#pragma once
#include "Entity.h"

#include <SFML/Graphics.hpp>

class HighscoreDisplay :
	public Entity
{
public:
	HighscoreDisplay();
	virtual ~HighscoreDisplay();

	virtual void Tick() override;

private:
	sf::Text _text;
};

