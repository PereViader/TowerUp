#include "stdafx.h"
#include "GameplayManager.h"


GameplayManager::GameplayManager() :
	Entity("GameplayManager", EntityType::World)
{
}


GameplayManager::~GameplayManager()
{
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
