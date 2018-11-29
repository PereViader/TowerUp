#include "stdafx.h"
#include "Game.h"


Game::Game() :
	_moduleRender(new ModuleRender()),
	_moduleInput(new ModuleInput()),
	_moduleEntities(new ModuleEntities()),
	_moduleCamera(new ModuleCamera()),
	_moduleTime(new ModuleTime()),
	_moduleCollision(new ModuleCollision())
{
	_modules.push_back(_moduleRender.get()); // the first because it will wait for target fps
	_modules.push_back(_moduleInput.get());
	_modules.push_back(_moduleTime.get());
	_modules.push_back(_moduleCamera.get());
	_modules.push_back(_moduleEntities.get());
	_modules.push_back(_moduleCollision.get()); // must be placed after moduleEntities
}

Game::~Game()
{
}

bool Game::Init()
{
	bool initOk = true;
	for (auto module = _modules.begin(); module != _modules.end() && initOk; ++module)
	{
		initOk = (*module)->Init();
	}

	return initOk;
}

GameExitStatus ExitStatusForGame(UpdateStatus updateStatus)
{
	switch (updateStatus)
	{
	case UpdateStatus::Continue:
	case UpdateStatus::Stop:
		return GameExitStatus::Ok;
	case UpdateStatus::Error:
		return GameExitStatus::Error;
	}
}

GameExitStatus Game::Play()
{
	if (!Init())
	{
		return GameExitStatus::Error;
	}

	UpdateStatus updateStatus = UpdateStatus::Continue;
	while (updateStatus == UpdateStatus::Continue)
	{
		updateStatus = Loop();
	}

	return ExitStatusForGame(updateStatus);
}

ModuleInput & Game::Input()
{
	return *_moduleInput;
}

ModuleRender & Game::Render()
{
	return *_moduleRender;
}

ModuleEntities & Game::Entities()
{
	return *_moduleEntities;
}

ModuleCamera & Game::Camera()
{
	return *_moduleCamera;
}

ModuleTime & Game::Time()
{
	return *_moduleTime;
}

ModuleCollision & Game::Collision()
{
	return *_moduleCollision;
}

UpdateStatus Game::Loop()
{
	UpdateStatus updateStatus = UpdateStatus::Continue;

	for (auto it = _modules.begin(); it != _modules.end() && updateStatus == UpdateStatus::Continue; ++it)
	{
		updateStatus = (*it)->PreUpdate();
	}

	for (auto it = _modules.begin(); it != _modules.end() && updateStatus == UpdateStatus::Continue; ++it)
	{
		updateStatus = (*it)->Update();
	}

	for (auto it = _modules.begin(); it != _modules.end() && updateStatus == UpdateStatus::Continue; ++it)
	{
		updateStatus = (*it)->PostUpdate();
	}

	return updateStatus;
}

