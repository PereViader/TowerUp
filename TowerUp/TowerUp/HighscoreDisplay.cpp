#include "stdafx.h"
#include "HighscoreDisplay.h"

#include "Game.h"


HighscoreDisplay::HighscoreDisplay() :
	Entity("HighscoreDisplay", EntityType::UI)
{
	_text.setFont(*game->Resources().GetFont(FontType::Sansation));
	_text.setCharacterSize(40);
	_text.setPosition(170.f, 150.f);
	_text.setFillColor(sf::Color::White);
}


HighscoreDisplay::~HighscoreDisplay()
{
}

void HighscoreDisplay::Init()
{
	if (!game->Storage().HasValue("Highscore"))
	{
		game->Storage().SetInt("Highscore", 0);
	}

	_text.setString("HighScore: " + std::to_string(game->Storage().GetInt("Highscore")));
}

void HighscoreDisplay::Tick()
{
	_text.setPosition(GetTransformable().getPosition());
	game->Render().Draw(_text, GetEntityType());
}
