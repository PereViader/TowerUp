#include "stdafx.h"
#include "GameplaySceneLoader.h"

#include "Game.h"
#include "TowerBlock.h"

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
	entities.AddEntityAndAttatchToRoot(new TowerBlock("Block"));
}
