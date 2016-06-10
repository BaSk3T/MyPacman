#include <vector>
#include "CollisionBox.h"
#include "GameObject.h"
#include "System.h"
#include "SystemGraphics.h"
#include "SystemInput.h"
#include "Level.h"

#include "PacmanGraphicsComponent.h"
#include "PacmanInputComponent.h"
#include "PacmanPhysicsComponent.h"

#pragma once
class World
{
public:
	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 640;

	std::vector<GameObject*> objects;

	World();
	~World();

	void run(System &system, SystemGraphics &systemGraphics, SystemInput &systemInput);
	bool checkCollision(CollisionBox const &a, CollisionBox const &b);
	bool isInRangeOf(CollisionBox const &a, CollisionBox const &b, unsigned int range);

private:
	static const int delay = 1000 / 60;
};

