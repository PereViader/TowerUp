#pragma once
#include "Entity.h"


class Ground :
	public Entity
{
public:
	Ground();
	virtual ~Ground();

	virtual void Init() override;
	virtual void Tick() override;
	virtual void Destroy() override;

public:
	Collidable _collidable;
	sf::RectangleShape _shape;
};

