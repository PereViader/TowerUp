#include "stdafx.h"
#include "LifeDisplay.h"

#include "Game.h"

LifeDisplay::LifeDisplay() :
	Entity("LifeDisplay", EntityType::UI)
{
	_text.setFont(*game->Resources().GetFont(FontType::Sansation));
	_text.setCharacterSize(40);
	_text.setFillColor(sf::Color::White);

	SetLifeCount(-1);
}


LifeDisplay::~LifeDisplay()
{
}

void LifeDisplay::Tick()
{
	_text.setPosition(GetTransformable().getPosition());
	game->Render().Draw(_text, GetEntityType());
}

void LifeDisplay::SetLifeCount(int value)
{
	_text.setString("Lifes: " + std::to_string(value));
}
