// TowerUp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <memory>

#include "Game.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

Game* game; // Declare the external Game object in "Game.h"

int main(char ** args)
{
	LOG(INFO) << "========================================";
	LOG(INFO) << "           Application start";
	LOG(INFO) << "========================================\n\n";

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