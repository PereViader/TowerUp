#include "stdafx.h"
#include "Tower.h"
#include "Game.h"

#include "GameplayManager.h"
#include "TowerBlock.h"
#include "Ground.h"
#include "CollisionInfo.h"
#include "easylogging++.h"

Tower::Tower() :
	_gameplayManager(static_cast<GameplayManager*>(game->Entities().FindByName("GameplayManager"))),
	Entity("Tower", EntityType::World)
{
}


Tower::~Tower()
{
}

void Tower::TryPlaceBlock(Block & block, Ground & ground, const CollisionInfo & collisionInfo)
{
	if (_topMostBlock == nullptr)
	{
		PlaceFirstBlock(collisionInfo.point);
	}
	else
	{
		_gameplayManager->LoseLifePoint();
	}
}

void Tower::TryPlaceBlock(Block & block, TowerBlock & towerBlock, const CollisionInfo & collisionInfo)
{
	StackPosition stackPosition;
	if (towerBlock.CanPlaceBlockOnTop(block, collisionInfo, stackPosition))
	{
		StackBlock(stackPosition);
	}
	else
	{
		_gameplayManager->LoseLifePoint();
	}
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
		return sf::Vector2f(-20, -40);
	case StackPosition::Right:
		return sf::Vector2f(20, -40);
	default: //Remove Warning
	case StackPosition::Center:
		return sf::Vector2f(0, -40);
	}
}

sf::Vector2f Tower::StackPositionToPosition(StackPosition stackPosition) const
{
	return _topMostBlock->GetTransformable().getPosition() + StackPositionVector(stackPosition);
}