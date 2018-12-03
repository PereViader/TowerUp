#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>

enum class ScoreReward
{
	Low = 100,
	High = 200
};

enum class BlockPlacement
{
	Success,
	Failure
};

class Camera;
class Swing;
class ScoreDisplay;
class LifeDisplay;

class GameplayManager :
	public Entity
{
public:
	GameplayManager();
	virtual ~GameplayManager();

	virtual void Init() override;
	virtual void LateTick() override;

	void NextBlock(BlockPlacement);
	void AwardScore(ScoreReward);
	void LoseLifePoint();
	void EndGameplay();

private:
	void PlaceBlockAtPosition(const sf::Vector2f& position);

private:
	int _lifePoints = 0;
	int _score = 0;
	float _currentPlacementCooldown = 0;

	std::shared_ptr<sf::Music> _music;
	std::shared_ptr<sf::SoundBuffer> _loseLifeSound;
	std::shared_ptr<sf::SoundBuffer> _placeBlock;

	ScoreDisplay* _scoreDisplay;
	LifeDisplay* _lifeDisplay;
	Camera* _camera;
	Swing* _swing;
};

