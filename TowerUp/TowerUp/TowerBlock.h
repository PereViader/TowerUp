#pragma once

#include "Entity.h"
#include "Tower.h"
#include <SFML\Graphics\RectangleShape.hpp>

class Block;

class TowerBlock :
	public Entity
{
public:
	TowerBlock();
	virtual ~TowerBlock();

	virtual void Init() override;
	virtual void Tick() override;
	virtual void Destroy() override;

	//void OnCollision(const CollisionInfo & info);
	void SetIsTopBlock(bool value);
	bool IsTopBlock() const;
	bool CanPlaceBlockOnTop(const Block&, const CollisionInfo&, StackPosition&);
private:
	bool ExtractStackPosition(const Block&, const CollisionInfo&, StackPosition&);

private:
	Collidable _collidable;
	sf::RectangleShape _shape;

	bool _isTopBlock = false;
};