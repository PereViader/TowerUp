#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

struct CollisionInfo;
class Entity;

class Collidable 
	: public sf::Drawable
{
	friend class ModuleCollision;

public:
	Collidable(Entity& entity, const sf::Vector2f& size);
	Collidable(Entity& entity, const sf::Vector2f& size, const sf::Vector2f& origin);
	virtual ~Collidable();

	const sf::Transformable& GetTransformable() const;
	const sf::Vector2f& GetSize() const;
	const sf::Vector2f& GetOrigin() const;
	const sf::FloatRect GetGlobalBounds() const;

	void UpdateTransformable(const sf::Transformable&);
	void SetSize(const sf::Vector2f&);
	void SetPivot(const sf::Vector2f&);
	void SetEntity(Entity& entity);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void OnCollision(const CollisionInfo&);

private:
	sf::RectangleShape _shape;
	sf::Transformable _transformable;
	Entity* _entity;
};