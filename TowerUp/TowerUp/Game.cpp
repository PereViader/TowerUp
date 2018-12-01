#include "stdafx.h"
#include "Game.h"

#include "MenuSceneLoader.h"
#include "GameplaySceneLoader.h"

#include "easylogging++.h"

Game::Game() :
	_moduleRender(new ModuleRender()),
	_moduleInput(new ModuleInput()),
	_moduleEntities(new ModuleEntities()),
	_moduleCamera(new ModuleCamera()),
	_moduleTime(new ModuleTime()),
	_moduleCollision(new ModuleCollision()),
	_moduleStorage(new ModuleStorage()),
	_moduleResources(new ModuleResources())
{
	_modules.push_back(_moduleRender.get()); // the first because it will wait for target fps
	_modules.push_back(_moduleStorage.get());
	_modules.push_back(_moduleResources.get());
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

	if (initOk)
	{
		ChangeScene(std::make_unique<GameplaySceneLoader>());
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
	default:
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

	if (updateStatus == UpdateStatus::Stop)
	{
		if (!End())
		{
			return GameExitStatus::Error;
		}
	}

	return ExitStatusForGame(updateStatus);
}

void Game::ChangeScene(std::unique_ptr<SceneLoader> sceneLoader)
{  
	LOG(INFO) << "Requested Scene Change";
	_sceneLoader = std::move(sceneLoader);
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

ModuleStorage & Game::Storage()
{
	return *_moduleStorage;
}

ModuleResources & Game::Resources()
{
	return *_moduleResources;
}

UpdateStatus Game::Loop()
{
	ExecuteSceneChangeIfAviable();

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

bool Game::End()
{
	bool endOk = true;
	for (auto module = _modules.begin(); module != _modules.end() && endOk; ++module)
	{
		endOk = (*module)->End();
	}

	return endOk;
}

void Game::ExecuteSceneChangeIfAviable()
{
	if (_sceneLoader)
	{
		for (auto module : _modules)
		{
			module->OnPreSceneChange();
		}

		_sceneLoader->LoadScene(*this);
		_sceneLoader.reset();
	}
}

