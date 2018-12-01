// TowerUp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "Game.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

Game* game;

int main(char ** args)
{
	LOG(INFO) << "Application start";
	game = new Game();
	GameExitStatus gameExitStatus = game->Play();

	switch (gameExitStatus)
	{
	case GameExitStatus::Ok:
		LOG(INFO) << "GameExitStatus::Ok";
		break;
	case GameExitStatus::Error:
		LOG(INFO) << "GameExitStatus::Error";
		break;
	}

	delete game;
	return 0;
}