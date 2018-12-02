#include "stdafx.h"
#include "TowerBlock.h"
#include "Block.h"
#include "Game.h"
#include "easylogging++.h"
#include "CollisionInfo.h"
#include "GameplayManager.h"
#include "Tower.h"

TowerBlock::TowerBlock() :
	_collidable(*this, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(20.0f, 40.0f)),
	_shape(sf::Vector2f(40.0f, 40.0f)),
	Entity("TowerBlock", EntityType::World)
{
	_shape.setTexture(game->Resources().GetTexture(TextureType::Block).get());
	_shape.setOrigin(sf::Vector2f(20.0f, 40.0f));
	game->Collision().AddCollidable(_collidable);
}


TowerBlock::~TowerBlock()
{
	game->Collision().RemoveCollidable(_collidable);
}

void TowerBlock::Tick()
{
	_collidable.UpdateTransformable(GetTransformable());
	_shape.setPosition(GetTransformable().getPosition());

	game->Render().Draw(_shape, GetEntityType());
	game->Render().DrawDebugCircle(GetTransformable().getPosition());
}

/*void TowerBlock::OnCollision(const CollisionInfo & info)
{
	if (info.collidable.GetEntity().GetName() == "Block")
	{
		Block& block = static_cast<Block&>(info.collidable.GetEntity());
		GameplayManager& gameplayManager = static_cast<GameplayManager&>(*game->Entities().FindByName("GameManager"));

		
		if (CanPlaceBlockOnTop(block))
		{
			tower.StackBlock(info.point);
			gameplayManager.AwardScore(ScoreReward::Low);
		}
	}
}*/

void TowerBlock::SetIsTopBlock(bool value)
{
	_isTopBlock = value;
}

bool TowerBlock::IsTopBlock() const
{
	return _isTopBlock;
}

bool TowerBlock::CanPlaceBlockOnTop(const Block &, const CollisionInfo &, StackPosition&)
{
	return false;
}
