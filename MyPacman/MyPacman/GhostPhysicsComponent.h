#include "MovingPhysicsComponent.h"

#pragma once
class GhostPhysicsComponent : public MovingPhysicsComponent
{
public:
	GhostPhysicsComponent();
	~GhostPhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(Message message, int objectId, GameObject &object);

private:
	static const int GHOST_WIDTH = 24;
	static const int GHOST_HEIGHT = 24;
	static const int VELOCITY = 2;

	void switchDirection(GameObject &object);
};

