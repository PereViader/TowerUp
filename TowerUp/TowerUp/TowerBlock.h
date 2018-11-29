#pragma once

#include "Entity.h"
#include <SFML\Graphics\RectangleShape.hpp>

class TowerBlock :
	public Entity
{
public:
	TowerBlock(const std::string& name);
	virtual ~TowerBlock();

	virtual void LateTick() override;

private:
	sf::RectangleShape _sprite;
};

