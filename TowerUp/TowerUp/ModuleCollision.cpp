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

CollisionInfo CreateCollisionInfoFor(const Collidable&, const Collidable&, const sf::FloatRect& intersection);
void CalculatePointAndDirection(const Collidable & originCollidable, const Collidable & destinyCollidable, const sf::FloatRect& intersection, sf::Vector2f& point, sf::Vector2f& direction);
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
		collidable1.OnCollision(CreateCollisionInfoFor(collidable1, collidable2, intersection));
		collidable2.OnCollision(CreateCollisionInfoFor(collidable2, collidable1, intersection));
	}
}

CollisionInfo CreateCollisionInfoFor(const Collidable &originCollidable, const Collidable &destinyCollidable, const sf::FloatRect& intersection)
{
	sf::Vector2f point, direction;
	CalculatePointAndDirection(originCollidable, destinyCollidable, intersection, point, direction);

	return CollisionInfo(point, direction, originCollidable);
}

//Tests which are the shortests to find the closest side
Side NearestSide(float leftTopDistance, float leftBottomDistance, float rightTopDistance, float rightBottomDistance)
{
	float distances[4]{ leftTopDistance , leftBottomDistance , rightTopDistance, rightBottomDistance };
	int first = 0, second = 1;
	for (int i = 1; i < 4; ++i)
	{
		if (distances[first] >= distances[i])
		{
			second = first;
			first = i;
		}
	}

	if (first + second == 1)//(first == 0 && second == 1 || first == 1 && second == 0)
	{
		return Side::LEFT;
	}
	else if (first + second == 2)//(first == 0 && second == 2 || first == 2 && second == 0)
	{
		return Side::TOP;
	}
	else if (first + second == 4)//(first == 1 && second == 3 || first == 3 && second == 1)
	{
		return Side::BOTTOM;
	}
	else
	{
		return Side::RIGHT;
	}
}


/*
Calculates the magnitude from each corner of the destiny Collidable to the center of the collision intersection
and projects the center of the intersection to the nearest side of the destiny collider
*/
void CalculatePointAndDirection(const Collidable & originCollidable, const Collidable & destinyCollidable, const sf::FloatRect& intersection, sf::Vector2f& point, sf::Vector2f& direction)
{
	const sf::FloatRect bounds = destinyCollidable.GetGlobalBounds();
	const sf::Vector2f intersectionCenter(intersection.left + intersection.width / 2.0f, intersection.top + intersection.height / 2.0f);
	const sf::Vector2f leftTopVector = intersectionCenter - sf::Vector2f(bounds.left, bounds.top);
	const sf::Vector2f leftBottomVector = intersectionCenter - sf::Vector2f(bounds.left, bounds.top + bounds.height);
	const sf::Vector2f rightTopVector = intersectionCenter - sf::Vector2f(bounds.left + bounds.width, bounds.top);
	const sf::Vector2f rightBottomVector = intersectionCenter - sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);

	const float leftTopDistance = leftTopVector.x * leftTopVector.x + leftTopVector.y * leftTopVector.y;
	const float leftBottomDistance = leftBottomVector.x * leftBottomVector.x + leftBottomVector.y * leftBottomVector.y;
	const float rightTopDistance = rightTopVector.x * rightTopVector.x + rightTopVector.y * rightTopVector.y;
	const float rightBottomDistance = rightBottomVector.x * rightBottomVector.x + rightBottomVector.y * rightBottomVector.y;

	switch (NearestSide(leftTopDistance, leftBottomDistance, rightTopDistance, rightBottomDistance))
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