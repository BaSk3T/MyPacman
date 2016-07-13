#include "MovingPhysicsComponent.h"
#include "World.h"

MovingPhysicsComponent::MovingPhysicsComponent()
	: PhysicsComponent(collisionBox)
{
}

MovingPhysicsComponent::~MovingPhysicsComponent()
{
}

bool MovingPhysicsComponent::takeTurnIfPossible(World &world, GameObject &object)
{
	bool success = true;
	double vx = object.velocityX;
	double vy = object.velocityY;

	if (this->changedDirection) {
		CollisionBox offsetCollisionBox = this->getCollisionBox();
		offsetCollisionBox.x += object.velocityX;
		offsetCollisionBox.y += object.velocityY;

		// check if ghost can take a turn in given direction
		if (world.collisionBoxIsColidingWith(ID_TILE, offsetCollisionBox)) {
			vx = this->previousVelocityX;
			vy = this->previousVelocityY;

			this->usedPreviousVelocity = true;
			object.send(STATE_CHANGE, object);
			success = false;
		}
	}

	object.x += vx;
	object.y += vy;

	if (success) {
		this->usedPreviousVelocity = false;
		this->previousVelocityX = object.velocityX;
		this->previousVelocityY = object.velocityY;
		object.send(STATE_ORIGINAL, object);
	}

	return success;
}

void MovingPhysicsComponent::shiftCollisionBox(double x, double y)
{
	this->collisionBox.x = x;
	this->collisionBox.y = y;
}