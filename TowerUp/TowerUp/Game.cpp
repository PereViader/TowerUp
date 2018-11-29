#include "stdafx.h"
#include "Game.h"


Game::Game() :
	_moduleRender(new ModuleRender()),
	_moduleInput(new ModuleInput()),
	_moduleEntities(new ModuleEntities()),
	_moduleCamera(new ModuleCamera()),
	_moduleTime(new ModuleTime())
{
	_modules.push_back(_moduleRender.get()); // needs to be the first because it will wait process for target fps
	_modules.push_back(_moduleInput.get());
	_modules.push_back(_moduleTime.get());
	_modules.push_back(_moduleCamera.get());
	_modules.push_back(_moduleEntities.get());
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

