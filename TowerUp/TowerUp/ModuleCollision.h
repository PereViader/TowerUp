#pragma once
#include "Module.h"

#include <list>
#include "Collidable.h"

class ModuleCollision :
	public Module
{
public:
	ModuleCollision();
	~ModuleCollision();

	virtual UpdateStatus Update() override;

	void AddCollidable(Collidable&);
	void RemoveCollidable(Collidable&);

	void ToggleCollidableDrawing();

private:
	void DrawCollidables() const;
	void CollisionCheck(Collidable& collidable1, Collidable& collidable2);

private:
	std::list<Collidable*> _collidables;
	bool _drawCollidables = true;
};

