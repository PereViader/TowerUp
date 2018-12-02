#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include "Game.h"

Camera::Camera() :
	_speed(CAMERA_SPEED),
	Entity("Camera", EntityType::World)
{
}


Camera::~Camera()
{
}

void Camera::AimNextBlock()
{
	_destiny += sf::Vector2f(0, -BLOCK_SIZE);
}

void Camera::Tick()
{
	const sf::Vector2f position =  GetTransformable().getPosition();
	GetTransformable().move((_destiny - position) * _speed * game->Time().GetDeltaTime());
	game->Camera().SetPosition(GetTransformable().getPosition());
}
