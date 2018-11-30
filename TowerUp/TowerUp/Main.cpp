// TowerUp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "Game.h"


Game* game;

int main(char ** args)
{
	game = new Game();
	GameExitStatus gameExitStatus = game->Play();

	switch (gameExitStatus)
	{
	case GameExitStatus::Ok:
		//@TODO: Debug OK
		break;
	case GameExitStatus::Error:
		//@TODO: Debug Error
		break;
	}

	delete game;
	return 0;
}