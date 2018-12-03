#include "stdafx.h"
#include "GameplayManager.h"

#include "Game.h"
#include "Block.h"
#include "Swing.h"
#include "Camera.h"

#include "MenuSceneLoader.h"
#include "ScoreDisplay.h"
#include "LifeDisplay.h"

#include "easylogging++.h"

GameplayManager::GameplayManager() :
	_lifePoints(GAMEPLAY_LIFES),
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
	_lifeDisplay = static_cast<LifeDisplay*>(game->Entities().FindByName("LifeDisplay"));


	_music = game->Resources().GetMusic(MusicType::Gameplay);
	_loseLifeSound = game->Resources().GetSound(SoundType::LoseLife);
	_placeBlock = game->Resources().GetSound(SoundType::PlaceBlock);

	game->Audio().PlayMusic(_music);
	_lifeDisplay->SetLifeCount(_lifePoints);
}

void GameplayManager::LateTick()
{
	if (_canPlaceBlock && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_canPlaceBlock = false;
		PlaceBlockAtPosition(_swing->GetEndSwingPosition());
	}
}

void GameplayManager::NextBlock(BlockPlacement blockPlacement)
{
	switch (blockPlacement)
	{
	case BlockPlacement::Success:
		_camera->AimNextBlock();
		break;
	case BlockPlacement::Failure:
		LoseLifePoint();
		break;
	default:
		break;
	}
	_canPlaceBlock = true;
}

void GameplayManager::AwardScore(ScoreReward scoreReward)
{
	_score += (int)scoreReward;
	_scoreDisplay->SetScore(_score);

	float pitch = scoreReward == ScoreReward::High ? GAMEPLAY_REWARD_HIGH_PITCH : 1.0f;
	game->Audio().PlaySoundBuffer(_placeBlock, pitch);
}

void GameplayManager::LoseLifePoint()
{
	_lifePoints -= 1;
	_lifeDisplay->SetLifeCount(_lifePoints);
	LOG(INFO) << "Lost life point. Current life points: " << _lifePoints;
	game->Audio().PlaySoundBuffer(_loseLifeSound);
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
