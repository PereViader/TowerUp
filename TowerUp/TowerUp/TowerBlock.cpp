#include "stdafx.h"
#include "TowerBlock.h"

#include "easylogging++.h"

#include "Globals.h"
#include "Game.h"
#include "GameplayManager.h"
#include "Block.h"
#include "Tower.h"
#include "CollisionInfo.h"

TowerBlock::TowerBlock() :
	_collidable(*this, sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), sf::Vector2f(BLOCK_SIZE/2.0f, BLOCK_SIZE)),
	_shape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
	Entity("TowerBlock", EntityType::World)
{
	_shape.setTexture(game->Resources().GetTexture(TextureType::Block).get());
	_shape.setOrigin(sf::Vector2f(BLOCK_SIZE/2.0f, BLOCK_SIZE));
}


TowerBlock::~TowerBlock()
{
}

void TowerBlock::Init()
{
	game->Collision().AddCollidable(_collidable);
}

void TowerBlock::Destroy()
{
	game->Collision().RemoveCollidable(_collidable);
}

void TowerBlock::Tick()
{
	_collidable.UpdateTransformable(GetTransformable());
	_shape.setPosition(GetTransformable().getPosition());

	game->Render().Draw(_shape, GetEntityType());
}

void TowerBlock::SetIsTopBlock(bool value)
{
	_isTopBlock = value;
}

bool TowerBlock::IsTopBlock() const
{
	return _isTopBlock;
}

bool TowerBlock::CanPlaceBlockOnTop(const Block & block, const CollisionInfo & collisionInfo, StackPosition& stackPosition)
{
	return _isTopBlock && ExtractStackPosition(block, collisionInfo, stackPosition);
}

bool TowerBlock::ExtractStackPosition(const Block & block, const CollisionInfo & collisionInfo, StackPosition & stackPosition)
{
	float positionDelta = block.GetTransformable().getPosition().x - GetTransformable().getPosition().x;

	if (std::abs(positionDelta) > BLOCK_SIZE/2.0f + OUTER_BLOCK_STACK_MARGIN)
	{
		//block is to the sides and can not be stacked
		return false;
	}

	if (positionDelta < -CENTER_BLOCK_STACK_MARGIN)
	{
		stackPosition = StackPosition::Left;
	}
	else if (positionDelta > CENTER_BLOCK_STACK_MARGIN)
	{
		stackPosition = StackPosition::Right;
	}
	else
	{
		stackPosition = StackPosition::Center;
	}
	
	return true;
}
