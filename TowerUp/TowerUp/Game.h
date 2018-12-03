#pragma once

#include <list>
#include <memory>

#include "Module.h"
#include "ModuleInput.h"
#include "ModuleEntities.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleTime.h"
#include "ModuleCollision.h"
#include "ModuleStorage.h"
#include "ModuleResources.h"
#include "ModuleAudio.h"

class SceneLoader;

enum class GameExitStatus
{
	Error,
	Ok
};

class Game
{
public:
	Game();
	~Game();

	GameExitStatus Play();

	void ChangeScene(std::unique_ptr<SceneLoader> sceneLoader);

	ModuleInput& Input();
	ModuleRender& Render();
	ModuleEntities& Entities();
	ModuleCamera& Camera();
	ModuleTime& Time();
	ModuleCollision& Collision();
	ModuleStorage& Storage();
	ModuleResources& Resources();
	ModuleAudio& Audio();

private:
	bool Init();
	UpdateStatus Loop();
	bool End();
	void ExecuteSceneChangeIfAviable();

private:
	std::list<Module*> _modules;
	std::unique_ptr<ModuleInput> _moduleInput;
	std::unique_ptr<ModuleEntities> _moduleEntities;
	std::unique_ptr<ModuleRender> _moduleRender;
	std::unique_ptr<ModuleCamera> _moduleCamera;
	std::unique_ptr<ModuleTime> _moduleTime;
	std::unique_ptr<ModuleCollision> _moduleCollision;
	std::unique_ptr<ModuleStorage> _moduleStorage;
	std::unique_ptr<ModuleResources> _moduleResources;
	std::unique_ptr<ModuleAudio> _moduleAudio;

	std::unique_ptr<SceneLoader> _sceneLoader;
};

extern Game* game;