#pragma once

#include "Module.h"
#include <list>
#include <string>

#include "Entity.h"

class ModuleEntities :
	public Module
{
public:
	ModuleEntities();
	~ModuleEntities();

	virtual bool Init() override;
	virtual UpdateStatus Update() override;

	Entity* RootEntity();

	Entity* AddEntityAndAttatchToRoot(Entity* entity);
	Entity* Instantiate();
	Entity* Instantiate(Entity* parent);
	void Destroy(Entity*);
	Entity* FindByName(std::string name);

public:
	std::list<Entity*> _entities;
	Entity * _rootEntity;
};

