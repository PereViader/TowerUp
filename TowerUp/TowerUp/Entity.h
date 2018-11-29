#pragma once

#include <string>
#include <list>
#include <memory>

#include <SFML\Main.hpp>
#include <SFML\Graphics\Transformable.hpp>

#include "Component.h"
#include "Collidable.h"

class Entity
{
public:
	Entity(const std::string& name);
	virtual ~Entity();

	virtual void Tick();
	virtual void LateTick();

	const std::string& GetName();
	void SetName(const std::string& name);

	sf::Transformable& GetTransformable();
	sf::Transform GetTransform() const;
	
	const std::list<Entity*> GetChilderen() const;
	void BecomeChildOf(Entity*);
	
	virtual void OnCollision(const CollisionInfo&);

private:
	std::string _name;

	Entity * _parent;
	std::list<Entity*> _childeren;

	sf::Transformable _transformable;

	std::list<std::unique_ptr<Component>> _components;
};

