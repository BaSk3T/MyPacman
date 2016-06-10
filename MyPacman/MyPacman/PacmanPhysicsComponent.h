#include "PacmanGraphicsComponent.h"
#include "CollisionBox.h"
#include "GameObject.h"

#pragma once
class PacmanPhysicsComponent : public PhysicsComponent
{
public:
	PacmanPhysicsComponent();
	~PacmanPhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(int message, int objectId);

private:
	static const int CHARACTER_WIDTH = 24;
	static const int CHARACTER_HEIGHT = 24;

	CollisionBox collisionBox = {0, 0, PacmanGraphicsComponent::CHARACTER_WIDTH, PacmanGraphicsComponent::CHARACTER_HEIGHT};
};

