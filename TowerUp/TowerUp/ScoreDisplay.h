#pragma once
#include "Entity.h"

class ScoreDisplay :
	public Entity
{
public:
	ScoreDisplay();
	virtual ~ScoreDisplay();

	virtual void Init() override;
	virtual void Tick() override;

	void AddScore(int value);
	void RemoveScore(int value);
	void SetScore(int value);
	int GetScore() const;

private:
	void UpdateScoreText();

private:
	sf::Text _text;
	int _score = 0;
};

