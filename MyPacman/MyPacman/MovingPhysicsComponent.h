#include "GameObject.h"
#include "CollisionBox.h"

#pragma once
class MovingPhysicsComponent : public PhysicsComponent
{
public:
	MovingPhysicsComponent();
	~MovingPhysicsComponent();

protected:
	static const int ID_TILE = 0;

	double previousVelocityX = 2;
	double previousVelocityY = 2;
	bool usedPreviousVelocity = false;
	bool changedDirection = false;

	bool takeTurnIfPossible(World &world, GameObject &object);
	void shiftCollisionBox(double x, double y);
};

