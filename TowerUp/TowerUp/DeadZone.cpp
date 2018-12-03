#include "stdafx.h"
#include "DeadZone.h"
#include "Globals.h"
#include "Game.h"

DeadZone::DeadZone() :
	_collidable(*this, sf::Vector2f((float)WINDOW_WIDTH, 300.f)),
	Entity("DeadZone", EntityType::World)
{
}

DeadZone::~DeadZone()
{
}

void DeadZone::Init()
{
	game->Collision().AddCollidable(_collidable);
}

void DeadZone::Destroy()
{
	game->Collision().RemoveCollidable(_collidable);
}


void DeadZone::LateTick()
{
	if (_followingEntity != nullptr)
	{
		const sf::Vector2f currentPosition = _followingEntity->GetTransformable().getPosition();
		const sf::Vector2f delta = currentPosition - _previousPosition;
		_previousPosition = currentPosition;

		GetTransformable().move(delta);
	}

	_collidable.UpdateTransformable(GetTransformable());
}

void DeadZone::Follow(Entity * entity)
{
	_previousPosition = entity->GetTransformable().getPosition();
	_followingEntity = entity;
}
