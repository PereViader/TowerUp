#pragma once
#include "SceneLoader.h"
class MenuSceneLoader :
	public SceneLoader
{
public:
	MenuSceneLoader();
	virtual ~MenuSceneLoader();

	virtual void LoadScene(Game&) const;
};

