#include "stdafx.h"
#include "MenuManager.h"
#include "Game.h"
#include "ModuleResources.h"

MenuManager::MenuManager() :
	Entity("MenuManager", EntityType::World)
{
}


MenuManager::~MenuManager()
{
}

void MenuManager::Init()
{
	_menuMusic = game->Resources().GetMusic(MusicType::Menu);
	game->Audio().PlayMusic(_menuMusic);
}
