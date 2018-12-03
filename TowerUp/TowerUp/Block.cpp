#include "stdafx.h"
#include "Block.h"

#include "easylogging++.h"
#include "Globals.h"
#include "Game.h"
#include "ModuleTime.h"
#include "CollisionInfo.h"
#include "Ground.h"
#include "TowerBlock.h"
#include "Tower.h"


Block::Block() :
	_collidable(*this, sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
	_shape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
	Entity("Block", EntityType::World)
{
	_shape.setTexture(game->Resources().GetTexture(TextureType::Block).get());
	_shape.setOrigin(sf::Vector2f(BLOCK_SIZE/2.0f, BLOCK_SIZE/2.0f));
}


Block::~Block()
{
}

void Block::Init()
{
	game->Collision().AddCollidable(_collidable);
}

void Block::Destroy()
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
	else
	{
		GameplayManager & gameplayManager = static_cast<GameplayManager&>(*game->Entities().FindByName("GameplayManager"));
		gameplayManager.NextBlock(BlockPlacement::Failure);
	}

	game->Entities().Destroy(this);
}
