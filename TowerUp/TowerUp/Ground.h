#pragma once
#include "Entity.h"


class Ground :
	public Entity
{
public:
	Ground();
	virtual ~Ground();

	virtual void Tick() override;

public:
	Collidable _collidable;
};

