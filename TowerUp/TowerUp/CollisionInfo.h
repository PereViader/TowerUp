#pragma once

#include <SFML/System/Vector2.hpp>

class Collidable;

struct CollisionInfo
{
	CollisionInfo(const sf::Vector2f& point, const sf::Vector2f& globalPoint, const sf::Vector2f& direction, const Collidable& collidable);

	const sf::Vector2f localPoint;
	const sf::Vector2f globalPoint;
	const sf::Vector2f direction;
	const Collidable& collidable;
};
