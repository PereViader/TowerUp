#pragma once
#include "Entity.h"
#include "GameplayManager.h"

class TowerBlock;
class Ground;
class Block;

enum class StackPosition
{
	Left,
	Center,
	Right
};

class Tower :
	public Entity
{
public:
	Tower();
	virtual ~Tower();

	virtual void Init() override;

	void TryPlaceBlock(Block&, Ground&, const CollisionInfo &);
	void TryPlaceBlock(Block&, TowerBlock&, const CollisionInfo &);

	void PlaceFirstBlock(const sf::Vector2f& position);
	void StackBlock(StackPosition);
private:
	ScoreReward StackPositionToScore(StackPosition) const;
	sf::Vector2f StackPositionToPosition(StackPosition) const;

private:
	TowerBlock * _topMostBlock = nullptr;

	GameplayManager* _gameplayManager;
};

