#include "stdafx.h"
#include "GameplaySceneLoader.h"

#include "Game.h"
#include "TowerBlock.h"
#include "Block.h"
#include "Ground.h"

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

	Block * block = static_cast<Block*>(entities.AddEntityAndAttatchToRoot(new Block()));
	block->GetTransformable().setPosition(sf::Vector2f(0, -100));
	block->SetVelocity(sf::Vector2f(0, 20));

	Ground * ground = static_cast<Ground*>(entities.AddEntityAndAttatchToRoot(new Ground()));
	ground->GetTransformable().setPosition(sf::Vector2f(0, 0));
}
