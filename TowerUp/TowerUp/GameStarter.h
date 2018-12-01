#pragma once
#include "Entity.h"


class GameStarter :
	public Entity
{
public:
	GameStarter();
	virtual ~GameStarter();

	virtual void Tick() override;

private:
	void StartGame();

private:
	sf::Text _text;
};

