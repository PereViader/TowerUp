#include "stdafx.h"
#include "Entity.h"
#include "Game.h"


Entity::Entity(const std::string& name, EntityType entityType) :
	_entityType(entityType),
	_name(name)
{
}

Entity::~Entity()
{
}

void Entity::Init()
{
}

void Entity::Tick()
{
}

void Entity::LateTick()
{

}

void Entity::Destroy()
{
}

EntityType Entity::GetEntityType() const
{
	return _entityType;
}

const std::string & Entity::GetName()
{
	return _name;
}

void Entity::SetName(const std::string & name)
{
	_name = name;
}

sf::Transformable & Entity::GetTransformable()
{
	return _transformable;
}

const sf::Transformable & Entity::GetTransformable() const
{
	return _transformable;
}

sf::Transform Entity::GetTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	if (_parent != nullptr)
	{
		transform.combine(_transformable.getTransform());
	}
	return transform;
}

const std::list<Entity*> Entity::GetChilderen() const
{
	return _childeren;
}

void Entity::BecomeChildOf(Entity * newParent)
{
	if (newParent != nullptr)
	{
		if (this->_parent != nullptr)
		{
			this->_parent->_childeren.remove(this);
		}

		this->_parent = newParent;
		this->_parent->_childeren.push_back(this);
	}
}

void Entity::OnCollision(const CollisionInfo &)
{
}
