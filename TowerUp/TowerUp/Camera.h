#pragma once
#include "Entity.h"

class Camera :
	public Entity
{
public:
	Camera();
	virtual ~Camera();

	void AimNextBlock();
	virtual void Tick() override;

private:
	sf::Vector2f _destiny;
	float _speed;
};

