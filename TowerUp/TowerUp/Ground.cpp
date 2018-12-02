#include "stdafx.h"
#include "Ground.h"
#include "TowerBlock.h"
#include "Globals.h"
#include "Game.h"


Ground::Ground() :
	_collidable(*this, 
		sf::Vector2f((float)WINDOW_WIDTH, 300.0f),
		sf::Vector2f((float)WINDOW_WIDTH/2.0f, 0.0f)),
	_shape(sf::Vector2f((float)WINDOW_WIDTH, 300.0f)),
	Entity("Ground", EntityType::World)
{
	_shape.setOrigin(sf::Vector2f((float)WINDOW_WIDTH/2.0f, 0.0f));
	_shape.setTexture(game->Resources().GetTexture(TextureType::Ground).get());
	game->Collision().AddCollidable(_collidable);
}

Ground::~Ground()
{
	game->Collision().RemoveCollidable(_collidable);
}

void Ground::Tick()
{
	_collidable.UpdateTransformable(GetTransformable());
	game->Render().DrawDebugCircle(GetTransformable().getPosition());
	game->Render().Draw(_shape, GetEntityType());
}