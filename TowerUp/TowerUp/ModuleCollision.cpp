#include "stdafx.h"
#include "ModuleCollision.h"

#include <SFML/System/Vector2.hpp>
#include "Game.h"

#include "CollisionInfo.h"

enum class POINT_POSITION {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

CollisionInfo CreateCollisionInfoFor(const Collidable&, const Collidable&, const sf::FloatRect& intersection);
void CalculatePointAndDirection(const Collidable & originCollidable, const Collidable & destinyCollidable, const sf::FloatRect& intersection, sf::Vector2f& point, sf::Vector2f& direction);
POINT_POSITION DiscriminatePointPosition(float leftTopDistance, float leftBottomDistance, float rightTopDistance, float rightBottomDistance);


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
		game->Render().Draw(*collidable);
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
	sf::Vector2f direction, point;
	CalculatePointAndDirection(originCollidable, destinyCollidable, intersection, point, direction);

	return CollisionInfo(point, direction, originCollidable);
}

POINT_POSITION DiscriminatePointPosition(float leftTopDistance, float leftBottomDistance, float rightTopDistance, float rightBottomDistance)
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
		return POINT_POSITION::LEFT;
	}
	else if (first + second == 2)//(first == 0 && second == 2 || first == 2 && second == 0)
	{
		return POINT_POSITION::TOP;
	}
	else if (first + second == 4)//(first == 1 && second == 3 || first == 3 && second == 1)
	{
		return POINT_POSITION::BOTTOM;
	}
	else
	{
		return POINT_POSITION::RIGHT;
	}
}


//Calculates the magnitude from each corner of the rectangle to the point. Then tests which are the shortests to find the closest side and project the point to the side
void CalculatePointAndDirection(const Collidable & originCollidable, const Collidable & destinyCollidable, const sf::FloatRect& intersection, sf::Vector2f& point, sf::Vector2f& direction)
{
	const sf::FloatRect originBounds = originCollidable.GetGlobalBounds();
	const sf::Vector2f intersectionCenter(intersection.left + intersection.width / 2.0f, intersection.top - intersection.height / 2.0f);
	const sf::Vector2f leftTop = intersectionCenter - sf::Vector2f(originBounds.left, originBounds.top);
	const sf::Vector2f leftBottom = intersectionCenter - sf::Vector2f(originBounds.left, originBounds.top - originBounds.height);
	const sf::Vector2f rightTop = intersectionCenter - sf::Vector2f(originBounds.left + originBounds.width, originBounds.top);
	const sf::Vector2f rightBottom = intersectionCenter - sf::Vector2f(originBounds.left + originBounds.width, originBounds.top - originBounds.height);

	const float leftTopDistance = leftTop.x * leftTop.x + leftTop.y + leftTop.y;
	const float leftBottomDistance = leftBottom.x * leftBottom.x + leftBottom.y + leftBottom.y;
	const float rightTopDistance = rightTop.x * rightTop.x + rightTop.y + rightTop.y;
	const float rightBottomDistance = rightBottom.x * rightBottom.x + rightBottom.y + rightBottom.y;

	switch (DiscriminatePointPosition(leftTopDistance, leftBottomDistance, rightTopDistance, rightBottomDistance))
	{
	case POINT_POSITION::LEFT:
		point = sf::Vector2f(leftBottom.x, intersectionCenter.y);
		direction = sf::Vector2f(-1, 0);
		break;

	case POINT_POSITION::RIGHT:
		point = sf::Vector2f(rightBottom.x, intersectionCenter.y);
		direction = sf::Vector2f(1, 0);
		break;
	case POINT_POSITION::BOTTOM:
		point = sf::Vector2f(intersectionCenter.x, leftBottom.y);
		direction = sf::Vector2f(0, -1);
		break;
	case POINT_POSITION::TOP:
	default: // will never default, removes warning
		point = sf::Vector2f(intersectionCenter.x, leftTop.y);
		direction = sf::Vector2f(0, 1);
		break;
	}
}