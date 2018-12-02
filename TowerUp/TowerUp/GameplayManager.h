#pragma once
#include "Entity.h"

enum class ScoreReward
{
	Low = 100,
	High = 200
};

class ScoreDisplay;
class Camera;

class GameplayManager :
	public Entity
{
public:
	GameplayManager();
	virtual ~GameplayManager();

	virtual void Init() override;
	virtual void Tick() override;

	void NextBlock();
	void AwardScore(ScoreReward);
	void LoseLifePoint();
	void EndGameplay();

private:
	void PlaceBlockAtMousePosition();

private:
	int _lifePoints;
	int _score;

	float _currentPlacementCooldown;

	ScoreDisplay* _scoreDisplay;
	Camera* _camera;
};

