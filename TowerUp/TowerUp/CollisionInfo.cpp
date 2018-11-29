#include "stdafx.h"
#include "CollisionInfo.h"


CollisionInfo::CollisionInfo(const sf::Vector2f & point, const sf::Vector2f & direction, const Collidable & collidable) :
	point(point),
	direction(direction),
	collidable(collidable)
{
}