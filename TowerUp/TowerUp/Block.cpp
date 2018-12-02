#include "stdafx.h"
#include "Block.h"

#include "Game.h"
#include "ModuleTime.h"
#include "easylogging++.h"
#include "CollisionInfo.h"
#include "Ground.h"
#include "TowerBlock.h"
#include "Tower.h"


Block::Block() :
	_collidable(*this, sf::Vector2f(40.0f,40.0f)),
	_shape(sf::Vector2f(40.0f, 40.0f)),
	Entity("Block", EntityType::World)
{
	_shape.setTexture(game->Resources().GetTexture(TextureType::Block).get());
	_shape.setOrigin(sf::Vector2f(20.0f, 20.0f));
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
	_shape.setPosition(GetTransformable().getPosition());

	game->Render().Draw(_shape, GetEntityType());
	game->Render().DrawDebugCircle(GetTransformable().getPosition());
}

void Block::OnCollision(const CollisionInfo & info)
{
	//LOG(INFO) << "Collision at: " + std::to_string(info.point.x) + ", " + std::to_string(info.point.y);
	Tower& tower = static_cast<Tower&>(*game->Entities().FindByName("Tower"));
	if (info.collidable.GetEntity().GetName() == "Ground")
	{
		Ground & ground = static_cast<Ground&>(info.collidable.GetEntity());
		tower.TryPlaceBlock(*this, ground, info);
	}
	else if (info.collidable.GetEntity().GetName() == "TowerBlock")
	{
		TowerBlock & towerBlock = static_cast<TowerBlock&>(info.collidable.GetEntity());
		tower.TryPlaceBlock(*this, towerBlock, info);
	}
	game->Entities().Destroy(this);
}
