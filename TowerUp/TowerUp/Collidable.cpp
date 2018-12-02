#include "stdafx.h"

#include "Collidable.h"
#include "Entity.h"


Collidable::Collidable(Entity & entity, const sf::Vector2f & size) :
	Collidable(entity, size, sf::Vector2f(size.x/2.0f, size.y/2.0f))
{
}

Collidable::Collidable(Entity& entity, const sf::Vector2f & size, const sf::Vector2f & origin) :
	_entity(&entity),
	_shape(size)
{
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineThickness(3);
	_shape.setOutlineColor(sf::Color::Red);
	_shape.setOrigin(origin);
}

Collidable::~Collidable()
{

}

const sf::Transformable& Collidable::GetTransformable() const
{
	return _transformable;
}

const sf::Vector2f & Collidable::GetSize() const
{
	return _shape.getSize();
}

const sf::Vector2f & Collidable::GetOrigin() const
{
	return _shape.getOrigin();
}

const sf::FloatRect Collidable::GetGlobalBounds() const
{
	return _shape.getGlobalBounds();
}

Entity & Collidable::GetEntity() const
{
	return *_entity;
}

void Collidable::UpdateTransformable(const sf::Transformable &transformable)
{
	_transformable = transformable;

	_shape.setPosition(transformable.getPosition());
	_shape.setRotation(transformable.getRotation());
	_shape.setScale(transformable.getScale());
}

void Collidable::SetSize(const sf::Vector2f &size)
{
	_shape.setSize(size);
}

void Collidable::SetPivot(const sf::Vector2f &origin)
{
	_shape.setOrigin(origin);
}

void Collidable::SetEntity(Entity & entity)
{
	_entity = &entity;
}

void Collidable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}

void Collidable::OnCollision(const CollisionInfo & collisionInfo)
{
	_entity->OnCollision(collisionInfo);
}