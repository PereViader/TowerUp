#pragma once
#include "Entity.h"

class Swing :
	public Entity
{
public:
	Swing();
	virtual ~Swing();

	virtual void Init() override;
	virtual void Tick() override;

	sf::Vector2f GetEndSwingPosition() const;

private:
	float _movementSign = 1;
	float _angluarSpeed;

	sf::RectangleShape _shape;
};

