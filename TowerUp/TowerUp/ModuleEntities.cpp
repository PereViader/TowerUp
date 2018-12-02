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
	_initList.push_back(entity);
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
	_initList.push_back(entity);
	entity->BecomeChildOf(parent);
	return entity;
}

void ModuleEntities::Destroy(Entity * entity)
{
	_destroySet.insert(entity);
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

void ModuleEntities::ExecuteEntityDestroy()
{
	while (_destroySet.size() > 0)
	{
		auto entityIt = _destroySet.begin();
		Entity* entity = *entityIt;

		entity->Destroy();

		for (Entity* child : entity->GetChilderen())
		{
			_destroySet.insert(child);
		}

		_entities.remove(entity);
		delete entity;

		_destroySet.erase(entityIt);
	}
	
}

void ModuleEntities::ExecuteEntityInit()
{
	for (auto* entity : _initList)
	{
		entity->Init();
		_entities.push_back(entity);
	}
	_initList.clear();
}

bool ModuleEntities::Init()
{
	return true;
}

UpdateStatus ModuleEntities::PreUpdate()
{
	ExecuteEntityDestroy();
	ExecuteEntityInit();

	return UpdateStatus::Continue;
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
