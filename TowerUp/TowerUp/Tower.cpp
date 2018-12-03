#include "stdafx.h"
#include "Tower.h"

#include "easylogging++.h"

#include "Globals.h"
#include "Game.h"
#include "GameplayManager.h"
#include "Ground.h"
#include "TowerBlock.h"
#include "CollisionInfo.h"

Tower::Tower() :
	Entity("Tower", EntityType::World)
{
}


Tower::~Tower()
{
}

void Tower::Init()
{
	_gameplayManager = static_cast<GameplayManager*>(game->Entities().FindByName("GameplayManager"));
}

void Tower::TryPlaceBlock(Block & block, Ground & ground, const CollisionInfo & collisionInfo)
{
	BlockPlacement blockPlacement = BlockPlacement::Failure;

	if (_topMostBlock == nullptr)
	{
		PlaceFirstBlock(collisionInfo.point);
		blockPlacement = BlockPlacement::Success;
	}

	_gameplayManager->NextBlock(blockPlacement);
}

void Tower::TryPlaceBlock(Block & block, TowerBlock & towerBlock, const CollisionInfo & collisionInfo)
{
	BlockPlacement blockPlacement = BlockPlacement::Failure;

	StackPosition stackPosition;
	if (towerBlock.CanPlaceBlockOnTop(block, collisionInfo, stackPosition))
	{
		StackBlock(stackPosition);
		blockPlacement = BlockPlacement::Success;
	}

	_gameplayManager->NextBlock(blockPlacement);
}

void Tower::PlaceFirstBlock(const sf::Vector2f & position)
{
	_gameplayManager->AwardScore(ScoreReward::High);
	_topMostBlock = static_cast<TowerBlock*>(game->Entities().AddEntityAndAttatchToRoot(new TowerBlock()));
	_topMostBlock->SetIsTopBlock(true);
	_topMostBlock->GetTransformable().setPosition(position);
}

void Tower::StackBlock(StackPosition stackPosition)
{
	_gameplayManager->AwardScore(StackPositionToScore(stackPosition));
	_topMostBlock->SetIsTopBlock(false);
	
	TowerBlock* newTopBlock = static_cast<TowerBlock*>(game->Entities().AddEntityAndAttatchToRoot(new TowerBlock()));
	newTopBlock->SetIsTopBlock(true);
	newTopBlock->GetTransformable().setPosition(StackPositionToPosition(stackPosition));

	_topMostBlock = newTopBlock;
}

ScoreReward Tower::StackPositionToScore(StackPosition stackPosition) const
{
	switch (stackPosition)
	{
	default: //Remove warning
	case StackPosition::Left:
	case StackPosition::Right:
		return ScoreReward::Low;
	case StackPosition::Center:
		return ScoreReward::High;
	}
}

sf::Vector2f StackPositionVector(StackPosition stackPosition)
{
	switch (stackPosition)
	{
	case StackPosition::Left:
		return sf::Vector2f(-BLOCK_SIZE/2.0f, -BLOCK_SIZE);
	case StackPosition::Right:
		return sf::Vector2f(BLOCK_SIZE/2.0f, -BLOCK_SIZE);
	default: //Remove Warning
	case StackPosition::Center:
		return sf::Vector2f(0, -BLOCK_SIZE);
	}
}

sf::Vector2f Tower::StackPositionToPosition(StackPosition stackPosition) const
{
	return _topMostBlock->GetTransformable().getPosition() + StackPositionVector(stackPosition);
}
