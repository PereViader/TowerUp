#include "stdafx.h"
#include "GameplaySceneLoader.h"

#include "Game.h"
#include "TowerBlock.h"

GameplaySceneLoader::GameplaySceneLoader()
{
}


GameplaySceneLoader::~GameplaySceneLoader()
{
}

void GameplaySceneLoader::LoadScene(Game& game) const
{
	ModuleEntities& entities = game.Entities();
	entities.AddEntityAndAttatchToRoot(new TowerBlock("Block"));
}
