#include "stdafx.h"
#include "GameStarter.h"

#include "Game.h"
#include "ModuleResources.h"
#include "GameplaySceneLoader.h"

GameStarter::GameStarter() :
	_text(),
	Entity("GameStarter", EntityType::UI)
{
	_text.setFont(*game->Resources().GetFont(FontType::Sansation));
	_text.setCharacterSize(30);
	_text.setString("Press ENTER or CLICK to start the game");
	const sf::FloatRect bounds = _text.getLocalBounds();
	_text.setOrigin(bounds.left + bounds.width / 2.f, 0);
}

GameStarter::~GameStarter()
{
}

void GameStarter::Tick()
{
	_text.setPosition(GetTransformable().getPosition());
	game->Render().Draw(_text, GetEntityType());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		StartGame();
	}
}

void GameStarter::StartGame()
{
	game->ChangeScene(std::make_unique<GameplaySceneLoader>());
}
