#include "stdafx.h"
#include "GameplayManager.h"
#include "Game.h"
#include "Block.h"
#include "easylogging++.h"
#include "ScoreDisplay.h"
#include "MenuSceneLoader.h"
#include "Camera.h"
#include "Swing.h"


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
	_camera = static_cast<Camera*>(game->Entities().FindByName("Camera"));
	_swing = static_cast<Swing*>(game->Entities().FindByName("Swing"));
}

void GameplayManager::LateTick()
{
	_currentPlacementCooldown -= game->Time().GetDeltaTime();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _currentPlacementCooldown < 0)
	{
		_currentPlacementCooldown = TIME_BETWEEN_BLOCKS;
		PlaceBlockAtPosition(_swing->GetEndSwingPosition());
	}
}

void GameplayManager::NextBlock()
{
	_camera->AimNextBlock();
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

void GameplayManager::PlaceBlockAtPosition(const sf::Vector2f& position)
{
	Block * block = static_cast<Block*>(game->Entities().AddEntityAndAttatchToRoot(new Block()));
	block->GetTransformable().setPosition(position);
	block->SetVelocity(sf::Vector2f(0, BLOCK_VELOCITY));
}
