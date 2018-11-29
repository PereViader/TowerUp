#include "stdafx.h"
#include "TowerBlock.h"
#include "Game.h"


TowerBlock::TowerBlock(const std::string& name) :
	Entity(name)
{
	_sprite.setSize(sf::Vector2f(18, 18));
	_sprite.setOutlineThickness(2);
	_sprite.setOutlineColor(sf::Color::Green);
	_sprite.setFillColor(sf::Color::Magenta);
}


TowerBlock::~TowerBlock()
{
}

void TowerBlock::LateTick()
{
	game->Render().Draw(_sprite);
}
