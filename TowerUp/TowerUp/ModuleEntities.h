#pragma once

#include "Module.h"
#include <list>
#include <set>
#include <string>

#include "Entity.h"

class ModuleEntities :
	public Module
{
public:
	ModuleEntities();
	~ModuleEntities();

	virtual bool Init() override;
	virtual UpdateStatus PreUpdate() override;
	virtual UpdateStatus Update() override;
	virtual void OnPreSceneChange() override;

	Entity* RootEntity();

	Entity* AddEntityAndAttatchToRoot(Entity* entity);
	Entity* Instantiate();
	Entity* Instantiate(Entity* parent);
	void Destroy(Entity*);
	Entity* FindByName(std::string name);

private:
	void ExecuteEntityDestroy();
	void ExecuteEntityInit();

public:
	std::list<Entity*> _entities;
	std::set<Entity*> _destroySet;
	std::list<Entity*> _initList;
	Entity * _rootEntity;
};

