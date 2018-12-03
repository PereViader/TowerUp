#pragma once
#include "Entity.h"
class DeadZone :
	public Entity
{
public:
	DeadZone();
	virtual ~DeadZone();

	virtual void Init() override;
	virtual void LateTick() override;
	virtual void Destroy() override;

	void Follow(Entity* entity);

private:
	Collidable _collidable;

	sf::Vector2f _previousPosition;
	Entity * _followingEntity;

};

