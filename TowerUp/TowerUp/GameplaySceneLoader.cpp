#include "stdafx.h"
#include "GameplaySceneLoader.h"

#include "Game.h"
#include "TowerBlock.h"
#include "Block.h"
#include "Ground.h"
#include "Tower.h"
#include "Swing.h"
#include "DeadZone.h"
#include "Camera.h"
#include "ScoreDisplay.h"
#include "LifeDisplay.h"

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

	Entity* camera = entities.AddEntityAndAttatchToRoot(new Camera());

	DeadZone * deadZone = static_cast<DeadZone*>(entities.AddEntityAndAttatchToRoot(new DeadZone()));
	deadZone->GetTransformable().setPosition(0, WINDOW_HEIGHT/2.0f);
	deadZone->Follow(camera);

	entities.AddEntityAndAttatchToRoot(new Swing());

	Entity* scoreDisplay = entities.AddEntityAndAttatchToRoot(new ScoreDisplay());
	scoreDisplay->GetTransformable().setPosition(10, 5);

	Entity* lifeDisplay = entities.AddEntityAndAttatchToRoot(new LifeDisplay());
	lifeDisplay->GetTransformable().setPosition(10, 50);

	GameplayManager * gameplayManager = static_cast<GameplayManager*>(entities.AddEntityAndAttatchToRoot(new GameplayManager()));

	Tower * tower = static_cast<Tower*>(entities.AddEntityAndAttatchToRoot(new Tower()));
	tower->GetTransformable().setPosition(sf::Vector2f(0, 0));

	Ground * ground = static_cast<Ground*>(entities.AddEntityAndAttatchToRoot(new Ground()));
	ground->GetTransformable().setPosition(sf::Vector2f(0, 0));
}
