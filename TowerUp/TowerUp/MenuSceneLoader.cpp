#include "stdafx.h"
#include "MenuSceneLoader.h"

#include "Game.h"
#include "ModuleEntities.h"
#include "HighscoreDisplay.h"
#include "TowerBlock.h"

MenuSceneLoader::MenuSceneLoader()
{
}

MenuSceneLoader::~MenuSceneLoader()
{
}

void MenuSceneLoader::LoadScene(Game & game) const
{
	ModuleEntities& entities = game.Entities();

	Entity* highscoreDisplay = entities.AddEntityAndAttatchToRoot(new HighscoreDisplay());
	highscoreDisplay->GetTransformable().setPosition(10, 5);

	//entities.AddEntityAndAttatchToRoot(new TowerBlock("Block"));
}
