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

	void NextBlock();
	void AwardScore(ScoreReward);
	void LoseLifePoint();
	void EndGameplay();

private:
	int _lifePoints;
};

