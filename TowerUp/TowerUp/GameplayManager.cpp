#include "stdafx.h"
#include "GameplayManager.h"
#include "Game.h"
#include "Block.h"
#include "easylogging++.h"

const float GameplayManager::PLACEMENT_COOLDOWN = 1.0f;


GameplayManager::GameplayManager() :
	Entity("GameplayManager", EntityType::World)
{
}


GameplayManager::~GameplayManager()
{
}

void GameplayManager::Tick()
{
	_currentPlacementCooldown -= game->Time().GetDeltaTime();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _currentPlacementCooldown < 0)
	{
		_currentPlacementCooldown = PLACEMENT_COOLDOWN;
		PlaceBlockAtMousePosition();
	}
}

void GameplayManager::NextBlock()
{
}

void GameplayManager::AwardScore(ScoreReward)
{
}

void GameplayManager::LoseLifePoint()
{

	_lifePoints -= 1;
	if (_lifePoints == 0)
	{
		EndGameplay();
	}
}

void GameplayManager::EndGameplay()
{
}

void GameplayManager::PlaceBlockAtMousePosition()
{
	Block * block = static_cast<Block*>(game->Entities().AddEntityAndAttatchToRoot(new Block()));
	block->GetTransformable().setPosition(game->Camera().MouseToWorldPosition());
	block->SetVelocity(sf::Vector2f(0, 100));
}
