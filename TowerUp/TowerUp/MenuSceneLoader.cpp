#include "stdafx.h"
#include "MenuSceneLoader.h"

#include "Game.h"
#include "ModuleEntities.h"
#include "HighscoreDisplay.h"

MenuSceneLoader::MenuSceneLoader()
{
}

MenuSceneLoader::~MenuSceneLoader()
{
}

void MenuSceneLoader::LoadScene(Game & game) const
{
	ModuleEntities& entities = game.Entities();
	entities.AddEntityAndAttatchToRoot(new HighscoreDisplay());
}
