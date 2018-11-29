#include "stdafx.h"
#include "ModuleEntities.h"

#include "TowerBlock.h" //TODO REMOVE

ModuleEntities::ModuleEntities()
{
	_rootEntity = new Entity("Root");
}


ModuleEntities::~ModuleEntities()
{
}

void ModuleEntities::AddEntityAndAttatchToRoot(Entity * entity)
{
	_entities.push_back(entity);
	entity->BecomeChildOf(_rootEntity);
}

Entity * ModuleEntities::Instantiate()
{
	return Instantiate(_rootEntity);
}

Entity * ModuleEntities::Instantiate(Entity * parent)
{
	Entity* entity = new Entity("Entity");
	_entities.push_back(entity);
	entity->BecomeChildOf(parent);
	return entity;
}

void ModuleEntities::Destroy(Entity * entity)
{
	for (auto child : entity->GetChilderen())
	{
		Destroy(child);
	}

	_entities.remove(entity);
	delete entity;
}

Entity* ModuleEntities::FindByName(std::string name)
{
	for (auto entity : _entities)
	{
		if (entity->GetName() == name)
		{
			return entity;
		}
	}

	return nullptr;
}

bool ModuleEntities::Init()
{
	TowerBlock* towerBlock = new TowerBlock("Block");
	AddEntityAndAttatchToRoot(towerBlock);
	return true;
}

UpdateStatus ModuleEntities::Update()
{
	for (auto entity : _entities)
	{
		entity->Tick();
	}

	for (auto entity : _entities)
	{
		entity->LateTick();
	}

	return UpdateStatus::Continue;
}

Entity * ModuleEntities::RootEntity()
{
	 return _rootEntity;
}
