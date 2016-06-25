#include "MovingPhysicsComponent.h"
#include "World.h"

MovingPhysicsComponent::MovingPhysicsComponent()
	: PhysicsComponent(collisionBox)
{
}

MovingPhysicsComponent::~MovingPhysicsComponent()
{
}

void MovingPhysicsComponent::takeTurnIfPossible(World &world, GameObject &object)
{
	CollisionBox offsetCollisionBox = this->getCollisionBox();
	offsetCollisionBox.x += object.velocityX;
	offsetCollisionBox.y += object.velocityY;

	// check if ghost can take a turn in given direction
	if (world.collisionBoxIsColidingWith(ID_TILE, offsetCollisionBox)) {
		object.x += this->previousVelocityX;
		object.y += this->previousVelocityY;

		this->usedPreviousVelocity = true;
		object.send(STATE_CHANGE, object.objectId);
	}
	else {
		object.x += object.velocityX;
		object.y += object.velocityY;
		this->usedPreviousVelocity = false;

		this->previousVelocityX = object.velocityX;
		this->previousVelocityY = object.velocityY;
		object.send(STATE_ORIGINAL, object.objectId);
	}
}

void MovingPhysicsComponent::shiftCollisionBox(double x, double y)
{
	this->collisionBox.x = x;
	this->collisionBox.y = y;
}