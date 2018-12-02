#pragma once
#include "Entity.h"

enum class ScoreReward
{
	Low = 100,
	High = 200
};

class GameplayManager :
	public Entity
{
public:
	GameplayManager();
	virtual ~GameplayManager();

	virtual void Tick() override;

	void NextBlock();
	void AwardScore(ScoreReward);
	void LoseLifePoint();
	void EndGameplay();

private:
	void PlaceBlockAtMousePosition();

private:
	int _lifePoints;

	float _currentPlacementCooldown;
	static const float PLACEMENT_COOLDOWN;
};

