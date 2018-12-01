#include "stdafx.h"
#include "Block.h"

#include "Game.h"
#include "ModuleTime.h"
#include "easylogging++.h"
#include "CollisionInfo.h"


Block::Block() :
	_collidable(*this, sf::Vector2f(40,40)),
	Entity("Block", EntityType::World)
{
	game->Collision().AddCollidable(_collidable);
}


Block::~Block()
{
	game->Collision().RemoveCollidable(_collidable);
}

void Block::SetVelocity(const sf::Vector2f & velocity)
{
	_velocity = velocity;
}

const sf::Vector2f & Block::GetVelocity() const
{
	return _velocity;
}

void Block::Tick()
{
	GetTransformable().move(_velocity * game->Time().GetDeltaTime());
	_collidable.UpdateTransformable(GetTransformable());
	game->Render().DrawDebugCircle(GetTransformable().getPosition());

}

void Block::OnCollision(const CollisionInfo & info)
{
	LOG(INFO) << "Collision at: " + std::to_string(info.point.x) + ", " + std::to_string(info.point.y);

	GetTransformable().setPosition(info.point);

}
