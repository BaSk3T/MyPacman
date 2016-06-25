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

	double previousVelocityX = 0;
	double previousVelocityY = 0;
	bool usedPreviousVelocity = false;

	void takeTurnIfPossible(World &world, GameObject &object);
	void shiftCollisionBox(double x, double y);
};

