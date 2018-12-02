#include "stdafx.h"
#include "ScoreDisplay.h"
#include "Game.h"

ScoreDisplay::ScoreDisplay() :
	Entity("ScoreDisplay", EntityType::UI)
{
	_text.setFont(*game->Resources().GetFont(FontType::Sansation));
	_text.setCharacterSize(40);
	_text.setPosition(170.f, 150.f);
	_text.setFillColor(sf::Color::White);
}


ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::Init()
{
	UpdateScoreText();
}

void ScoreDisplay::Tick()
{
	_text.setPosition(GetTransformable().getPosition());
	game->Render().Draw(_text, GetEntityType());
}

void ScoreDisplay::AddScore(int value)
{
	_score += value;
	UpdateScoreText();
}

void ScoreDisplay::RemoveScore(int value)
{
	_score -= value;
	UpdateScoreText();
}

void ScoreDisplay::SetScore(int value)
{
	_score = value;
	UpdateScoreText();
}

int ScoreDisplay::GetScore() const
{
	return _score;
}

void ScoreDisplay::UpdateScoreText()
{
	_text.setString("Score: " + std::to_string(_score));
}
