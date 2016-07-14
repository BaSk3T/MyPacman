#include <vector>
#include <deque>
#include "CollisionBox.h"
#include "GameObject.h"
#include "System.h"
#include "SystemGraphics.h"
#include "SystemInput.h"
#include "SystemFont.h"
#include "Timer.h"
#include "Level.h"
#include <sstream>

#include "PacmanGraphicsComponent.h"
#include "PacmanInputComponent.h"
#include "PacmanPhysicsComponent.h"

#include "GhostGraphicsComponent.h"
#include "GhostInputComponent.h"
#include "GhostPhysicsComponent.h"

#pragma once
class World
{
public:
	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 640;
	static const int COLLISION_RANGE = 50;
	static const int SCREEN_FPS = 60;
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	static const int OBJECT_TYPES = 4;

	std::vector<GameObject*> objects[OBJECT_TYPES];
	std::deque<CollisionBox> trail;

	World();
	~World();
	
	void run(System &system, SystemGraphics &systemGraphics, SystemInput &systemInput, SystemFont &systemFont);
	void resolveCollision(GameObject &sender);
	bool checkCollision(CollisionBox const &a, CollisionBox const &b);
	bool isInRangeOf(CollisionBox const &a, CollisionBox const &b, unsigned int range);
	bool collisionBoxIsColidingWith(int objectId, CollisionBox const &collisionBox);

private:
	static const int delay = 1000 / 60;
};

