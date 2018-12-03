#include "stdafx.h"
#include "MenuSceneLoader.h"

#include "Globals.h"
#include "Game.h"
#include "ModuleEntities.h"
#include "HighscoreDisplay.h"
#include "GameStarter.h"
#include "MenuManager.h"
#include "easylogging++.h"

MenuSceneLoader::MenuSceneLoader()
{
}

MenuSceneLoader::~MenuSceneLoader()
{
}

void MenuSceneLoader::LoadScene(Game & game) const
{
	LOG(INFO) << "Loading Menu Scene";

	ModuleEntities& entities = game.Entities();

	entities.AddEntityAndAttatchToRoot(new MenuManager());

	Entity* highscoreDisplay = entities.AddEntityAndAttatchToRoot(new HighscoreDisplay());
	highscoreDisplay->GetTransformable().setPosition(10, 5);

	Entity* gameStarter = entities.AddEntityAndAttatchToRoot(new GameStarter());
	gameStarter->GetTransformable().setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.0f);
}
