#include "stdafx.h"
#include "ModuleEntities.h"

#include "TowerBlock.h" //TODO REMOVE

ModuleEntities::ModuleEntities()
{
	_rootEntity = new Entity("Root", EntityType::World);
}


ModuleEntities::~ModuleEntities()
{
}

Entity * ModuleEntities::AddEntityAndAttatchToRoot(Entity * entity)
{
	_entities.push_back(entity);
	entity->BecomeChildOf(_rootEntity);
	return entity;
}

Entity * ModuleEntities::Instantiate()
{
	return Instantiate(_rootEntity);
}

Entity * ModuleEntities::Instantiate(Entity * parent)
{
	Entity* entity = new Entity("Entity", EntityType::World);
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

void ModuleEntities::OnPreSceneChange()
{
	Destroy(_rootEntity);
	_rootEntity = new Entity("Root", EntityType::World);
}

Entity * ModuleEntities::RootEntity()
{
	 return _rootEntity;
}
