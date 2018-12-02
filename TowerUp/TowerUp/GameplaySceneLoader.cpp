#include "stdafx.h"
#include "GameplaySceneLoader.h"

#include "Game.h"
#include "TowerBlock.h"
#include "Block.h"
#include "Ground.h"
#include "Tower.h"

#include "easylogging++.h"

GameplaySceneLoader::GameplaySceneLoader()
{
}


GameplaySceneLoader::~GameplaySceneLoader()
{
}

void GameplaySceneLoader::LoadScene(Game& game) const
{
	LOG(INFO) << "Loading Gameplay Scene";

	ModuleEntities& entities = game.Entities();

	GameplayManager * gameplayManager = static_cast<GameplayManager*>(entities.AddEntityAndAttatchToRoot(new GameplayManager()));

	Tower * tower = static_cast<Tower*>(entities.AddEntityAndAttatchToRoot(new Tower()));
	tower->GetTransformable().setPosition(sf::Vector2f(0, 0));

	Block * block = static_cast<Block*>(entities.AddEntityAndAttatchToRoot(new Block()));
	block->GetTransformable().setPosition(sf::Vector2f(0, -100));
	block->SetVelocity(sf::Vector2f(0, 50));

	Ground * ground = static_cast<Ground*>(entities.AddEntityAndAttatchToRoot(new Ground()));
	ground->GetTransformable().setPosition(sf::Vector2f(0, 0));
}
