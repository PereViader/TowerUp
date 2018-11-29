#pragma once

class Game;

class SceneLoader
{
public:
	virtual void LoadScene(Game&) const = 0;
};

