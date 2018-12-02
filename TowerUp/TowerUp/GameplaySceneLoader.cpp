#include "stdafx.h"
#include "GameplaySceneLoader.h"

#include "Game.h"
#include "TowerBlock.h"
#include "Block.h"
#include "Ground.h"
#include "Tower.h"
#include "HighscoreDisplay.h"

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

	Entity* highscoreDisplay = entities.AddEntityAndAttatchToRoot(new HighscoreDisplay());
	highscoreDisplay->GetTransformable().setPosition(10, 5);

	GameplayManager * gameplayManager = static_cast<GameplayManager*>(entities.AddEntityAndAttatchToRoot(new GameplayManager()));

	Tower * tower = static_cast<Tower*>(entities.AddEntityAndAttatchToRoot(new Tower()));
	tower->GetTransformable().setPosition(sf::Vector2f(0, 0));

	Ground * ground = static_cast<Ground*>(entities.AddEntityAndAttatchToRoot(new Ground()));
	ground->GetTransformable().setPosition(sf::Vector2f(0, 0));
}
