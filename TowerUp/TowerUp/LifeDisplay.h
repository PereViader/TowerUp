#pragma once
#include "Entity.h"


class LifeDisplay :
	public Entity
{
public:

	LifeDisplay();
	virtual ~LifeDisplay();

	virtual void Tick() override;

	void SetLifeCount(int value);

private:
	sf::Text _text;
};

