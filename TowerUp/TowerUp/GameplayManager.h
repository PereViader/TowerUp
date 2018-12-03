#pragma once
#include "Entity.h"

enum class ScoreReward
{
	Low = 100,
	High = 200
};

class ScoreDisplay;
class Camera;
class Swing;

class GameplayManager :
	public Entity
{
public:
	GameplayManager();
	virtual ~GameplayManager();

	virtual void Init() override;
	virtual void LateTick() override;

	void NextBlock();
	void AwardScore(ScoreReward);
	void LoseLifePoint();
	void EndGameplay();

private:
	void PlaceBlockAtPosition(const sf::Vector2f& position);

private:
	int _lifePoints;
	int _score;

	float _currentPlacementCooldown;

	ScoreDisplay* _scoreDisplay;
	Camera* _camera;
	Swing* _swing;
};

