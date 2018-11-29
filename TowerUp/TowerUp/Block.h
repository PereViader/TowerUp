#pragma once
#include "Entity.h"


class Block :
	public Entity
{
public:
	Block();
	virtual ~Block();

	virtual void Tick() override;

private:
	sf::Vector2f _velocity;
};

