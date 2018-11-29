#include "stdafx.h"
#include "CollisionInfo.h"


CollisionInfo::CollisionInfo(const sf::Vector2f & localPoint, const sf::Vector2f & globalPoint, const sf::Vector2f & direction, const Collidable & collidable) :
	localPoint(localPoint),
	globalPoint(globalPoint),
	direction(direction),
	collidable(collidable)
{
}