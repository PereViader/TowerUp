#include "stdafx.h"
#include "GameplayManager.h"
#include "Game.h"
#include "Block.h"
#include "easylogging++.h"
#include "ScoreDisplay.h"
#include "MenuSceneLoader.h"


GameplayManager::GameplayManager() :
	Entity("GameplayManager", EntityType::World)
{
}

GameplayManager::~GameplayManager()
{
}

void GameplayManager::Init()
{
	_scoreDisplay = static_cast<ScoreDisplay*>(game->Entities().FindByName("ScoreDisplay"));
}

void GameplayManager::Tick()
{
	_currentPlacementCooldown -= game->Time().GetDeltaTime();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _currentPlacementCooldown < 0)
	{
		_currentPlacementCooldown = TIME_BETWEEN_BLOCKS;
		PlaceBlockAtMousePosition();
	}
}

void GameplayManager::NextBlock()
{
}

void GameplayManager::AwardScore(ScoreReward scoreReward)
{
	_score += (int)scoreReward;
	_scoreDisplay->SetScore(_score);
}

void GameplayManager::LoseLifePoint()
{
	_lifePoints -= 1;
	LOG(INFO) << "Lost life point. Current life points: " << _lifePoints;
	if (_lifePoints <= 0)
	{
		EndGameplay();
	}
}

void GameplayManager::EndGameplay()
{
	int previousHighscore = game->Storage().GetInt("Highscore");
	if (_score > previousHighscore)
	{
		game->Storage().SetInt("Highscore", _score);
	}

	game->ChangeScene(std::make_unique<MenuSceneLoader>());
}

void GameplayManager::PlaceBlockAtMousePosition()
{
	Block * block = static_cast<Block*>(game->Entities().AddEntityAndAttatchToRoot(new Block()));
	block->GetTransformable().setPosition(game->Camera().MouseToWorldPosition());
	block->SetVelocity(sf::Vector2f(0, 100));
}
