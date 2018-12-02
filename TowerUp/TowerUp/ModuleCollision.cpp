#include "stdafx.h"
#include "ModuleCollision.h"

#include <SFML/System/Vector2.hpp>
#include "Game.h"

#include "CollisionInfo.h"

enum class Side {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

CollisionInfo BuildCollisionInfo(const Collidable&, const sf::FloatRect& intersection);
void CalculatePointAndDirection(const Collidable & collidable, const sf::FloatRect& intersection, sf::Vector2f& point, sf::Vector2f& direction);
Side NearestSide(float leftTopDistance, float leftBottomDistance, float rightTopDistance, float rightBottomDistance);

 
ModuleCollision::ModuleCollision()
{
}


ModuleCollision::~ModuleCollision()
{
}

UpdateStatus ModuleCollision::Update()
{
	for (auto it1 = _collidables.begin(); it1 != _collidables.end(); ++it1)
	{
		for (auto it2 = std::next(it1, 1); it2 != _collidables.end(); ++it2)
		{
			CollisionCheck(**it1, **it2);
		}
	}

	if (_drawCollidables)
	{
		DrawCollidables();
	}

	return UpdateStatus::Continue;
}

void ModuleCollision::AddCollidable(Collidable & collidable) 
{
	_collidables.push_back(&collidable);
}

void ModuleCollision::RemoveCollidable(Collidable & collidable)
{
	_collidables.remove(&collidable);
}

void ModuleCollision::ToggleCollidableDrawing()
{
	_drawCollidables = !_drawCollidables;
}

void ModuleCollision::DrawCollidables() const
{
	for (auto* collidable : _collidables)
	{
		game->Render().Draw(*collidable, EntityType::World);
	}
}

void ModuleCollision::CollisionCheck(Collidable & collidable1, Collidable & collidable2)
{
	sf::FloatRect intersection;
	bool doIntersect = collidable1.GetGlobalBounds().intersects(collidable2.GetGlobalBounds(), intersection);
	if (doIntersect)
	{
		collidable1.OnCollision(BuildCollisionInfo(collidable2, intersection));
		collidable2.OnCollision(BuildCollisionInfo(collidable1, intersection));
	}
}

CollisionInfo BuildCollisionInfo(const Collidable &collidable, const sf::FloatRect& intersection)
{
	sf::Vector2f point, direction;
	CalculatePointAndDirection(collidable, intersection, point, direction);

	return CollisionInfo(point, direction, collidable);
}

//Tests which are the shortests to find the closest side
Side NearestSide(float top, float bottom, float left, float right)
{
	float distances[4]{top , bottom, left, right};
	int min = 0;
	for (int i = 1; i < 4; ++i)
	{
		if (distances[min] > distances[i])
		{
			min = i;
		}
	}

	switch (min)
	{
	case 0:
	default: //Remove warning
		return Side::TOP;
	case 1:
		return Side::BOTTOM;
	case 2:
		return Side::LEFT;
	case 3:
		return Side::RIGHT;
	}
}


/*
Calculates the magnitude from each corner of the destiny Collidable to the center of the collision intersection
and projects the center of the intersection to the nearest side of the destiny collider
*/
void CalculatePointAndDirection(const Collidable & collidable, const sf::FloatRect& intersection, sf::Vector2f& point, sf::Vector2f& direction)
{
	const sf::FloatRect bounds = collidable.GetGlobalBounds();
	const sf::Vector2f intersectionCenter(intersection.left + intersection.width / 2.0f, intersection.top + intersection.height / 2.0f);
	const float topDistance = intersectionCenter.y - bounds.top;
	const float bottomDistance = bounds.top + bounds.height - intersectionCenter.y;
	const float leftDistance = intersectionCenter.x - bounds.left;
	const float rightDistance = bounds.left + bounds.width - intersectionCenter.x;

	/*const sf::Vector2f leftTopVector = intersectionCenter - sf::Vector2f(bounds.left, bounds.top);
	const sf::Vector2f leftBottomVector = intersectionCenter - sf::Vector2f(bounds.left, bounds.top + bounds.height);
	const sf::Vector2f rightTopVector = intersectionCenter - sf::Vector2f(bounds.left + bounds.width, bounds.top);
	const sf::Vector2f rightBottomVector = intersectionCenter - sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);

	const float leftTopDistance = leftTopVector.x * leftTopVector.x + leftTopVector.y * leftTopVector.y;
	const float leftBottomDistance = leftBottomVector.x * leftBottomVector.x + leftBottomVector.y * leftBottomVector.y;
	const float rightTopDistance = rightTopVector.x * rightTopVector.x + rightTopVector.y * rightTopVector.y;
	const float rightBottomDistance = rightBottomVector.x * rightBottomVector.x + rightBottomVector.y * rightBottomVector.y;*/

	switch (NearestSide(topDistance, bottomDistance, leftDistance, rightDistance))
	{
	case Side::LEFT:
		point = sf::Vector2f(bounds.left, intersectionCenter.y);
		direction = sf::Vector2f(-1, 0);
		break;

	case Side::RIGHT:
		point = sf::Vector2f(bounds.left + bounds.width, intersectionCenter.y);
		direction = sf::Vector2f(1, 0);
		break;
	case Side::BOTTOM:
		point = sf::Vector2f(intersectionCenter.x, bounds.top + bounds.height);
		direction = sf::Vector2f(0, 1);
		break;
	case Side::TOP:
	default: // will never default, removes warning
		point = sf::Vector2f(intersectionCenter.x, bounds.top);
		direction = sf::Vector2f(0, -1);
		break;
	}
}