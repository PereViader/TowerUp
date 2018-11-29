#pragma once
#include "SceneLoader.h"

class GameplaySceneLoader :
	public SceneLoader
{
public:
	GameplaySceneLoader();
	virtual ~GameplaySceneLoader();

	virtual void LoadScene(Game&) const override;
};

