#pragma once

#include <list>
#include <memory>

#include "Globals.h"

#include "Module.h"
#include "ModuleInput.h"
#include "ModuleEntities.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleTime.h"
#include "ModuleCollision.h"


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

	ModuleInput& Input();
	ModuleRender& Render();
	ModuleEntities& Entities();
	ModuleCamera& Camera();
	ModuleTime& Time();
	ModuleCollision& Collision();

private:
	bool Init();
	UpdateStatus Loop();

private:
	std::list<Module*> _modules;
	std::unique_ptr<ModuleInput> _moduleInput;
	std::unique_ptr<ModuleEntities> _moduleEntities;
	std::unique_ptr<ModuleRender> _moduleRender;
	std::unique_ptr<ModuleCamera> _moduleCamera;
	std::unique_ptr<ModuleTime> _moduleTime;
	std::unique_ptr<ModuleCollision> _moduleCollision;

};

extern Game* game;