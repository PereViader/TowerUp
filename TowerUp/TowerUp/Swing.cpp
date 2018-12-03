#include "stdafx.h"
#include "Swing.h"

#include "easylogging++.h"

#include "Globals.h"
#include "Game.h"

Swing::Swing() :
	_angluarSpeed(SWING_SPEED),
	_shape(sf::Vector2f(SWING_LENGHT, SWING_WIDTH)),
	Entity("Swing", EntityType::World)
{
	_shape.setOrigin(0,SWING_WIDTH / 2.0f);
	_shape.setFillColor(sf::Color::White);
}


Swing::~Swing()
{
}

void Swing::Init()
{
	GetTransformable().setRotation(90 + SWING_ANGLE / 2.0f);
	_movementSign = -1;
}

void Swing::Tick()
{
	float rotation = GetTransformable().getRotation();
	rotation += _movementSign * _angluarSpeed * game->Time().GetDeltaTime();
	//LOG(INFO) << rotation;
	
	if (rotation > 90 + SWING_ANGLE/2.0f)
	{
		rotation = 90 + SWING_ANGLE / 2.0f;
		_movementSign = -1;
	}
	else if(rotation < 90 - SWING_ANGLE / 2.0f)
	{
		rotation = 90 - SWING_ANGLE / 2.0f;
		_movementSign = 1;
	}


	GetTransformable().setRotation(rotation);
	GetTransformable().setPosition(game->Camera().ScreenToWorldPosition(sf::Vector2i(WINDOW_WIDTH / 2, 50)));

	_shape.setPosition(GetTransformable().getPosition());
	_shape.setRotation(GetTransformable().getRotation());

	game->Render().Draw(_shape, GetEntityType());
}

sf::Vector2f Swing::GetEndSwingPosition() const
{
	sf::Transform swingRotationTransform;
	swingRotationTransform.rotate(GetTransformable().getRotation(), GetTransformable().getPosition());
	return  swingRotationTransform.transformPoint(GetTransformable().getPosition() + sf::Vector2f(SWING_LENGHT, 0));
}
