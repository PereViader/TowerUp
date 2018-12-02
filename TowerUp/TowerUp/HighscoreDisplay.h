#pragma once
#include "Entity.h"

#include <SFML/Graphics.hpp>

class HighscoreDisplay :
	public Entity
{
public:
	HighscoreDisplay();
	virtual ~HighscoreDisplay();

	virtual void Init() override;
	virtual void Tick() override;

private:
	void UpdateHighscoreText();

private:
	sf::Text _text;
	int _previousHighscore = -1;
};