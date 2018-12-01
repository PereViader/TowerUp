#pragma once
#include "Entity.h"


class Block :
	public Entity
{
public:
	Block();
	virtual ~Block();

	void SetVelocity(const sf::Vector2f& velocity);
	const sf::Vector2f& GetVelocity() const;

	virtual void Tick() override;

	virtual void OnCollision(const CollisionInfo&) override;

private:
	sf::Vector2f _velocity;
	Collidable _collidable;
	sf::RectangleShape _shape;
};

