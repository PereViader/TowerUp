#include "stdafx.h"
#include "HighscoreDisplay.h"

#include "Game.h"

const std::string HIGHSCORE("Highscore");

HighscoreDisplay::HighscoreDisplay() :
	Entity("HighscoreDisplay", EntityType::UI)
{
	_text.setFont(*game->Resources().GetFont(FontType::Sansation));
	_text.setCharacterSize(40);
	_text.setPosition(170.f, 150.f);
	_text.setFillColor(sf::Color::White);

	if (!game->Storage().HasValue(HIGHSCORE))
	{
		game->Storage().SetInt(HIGHSCORE, 0);
	}
}


HighscoreDisplay::~HighscoreDisplay()
{
}

void HighscoreDisplay::Tick()
{
	UpdateHighscoreText();

	_text.setPosition(GetTransformable().getPosition());
	game->Render().Draw(_text, GetEntityType());
}

void HighscoreDisplay::UpdateHighscoreText()
{
	int currentHighscore = game->Storage().GetInt(HIGHSCORE);
	if (currentHighscore != _previousHighscore)
	{
		_text.setString("HighScore: " + std::to_string(currentHighscore));
		_previousHighscore = currentHighscore;
	}
}
