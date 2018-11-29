#include "stdafx.h"
#include "ModuleCollision.h"

#include "Game.h"

#include "CollisionInfo.h"

CollisionInfo CreateCollisionInfoFor(const Collidable&, const Collidable&, const sf::FloatRect& intersection);
sf::Vector2f CalculatePoint(const Collidable& originCollidable, const Collidable& destinyCollidable, const sf::FloatRect& intersection);
sf::Vector2f CalculateDirection(const Collidable& originCollidable, const sf::Vector2f& point);

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
	bool doIntersect = collidable1._shape.getGlobalBounds().intersects(collidable2._shape.getGlobalBounds(), intersection);
	if (doIntersect)
	{
		collidable1.OnCollision(CreateCollisionInfoFor(collidable1, collidable2, intersection));
		collidable2.OnCollision(CreateCollisionInfoFor(collidable2, collidable1, intersection));
	}
}

CollisionInfo CreateCollisionInfoFor(const Collidable &originCollidable, const Collidable &destinyCollidable, const sf::FloatRect& intersection)
{
	const sf::Vector2f globalPoint = CalculatePoint(originCollidable, destinyCollidable, intersection);
	const sf::Vector2f direction = CalculateDirection(originCollidable, globalPoint);

	return CollisionInfo(sf::Vector2f(), globalPoint, direction, originCollidable); //TODO Local Point
}

sf::Vector2f CalculatePoint(const Collidable & originCollidable, const Collidable & destinyCollidable, const sf::FloatRect& intersection)
{
	//TODO
	return sf::Vector2f();
}

sf::Vector2f CalculateDirection(const Collidable & originCollidable, const sf::Vector2f& point)
{
	//TODO
	return sf::Vector2f();
}
