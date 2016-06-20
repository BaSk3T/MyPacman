#include "PacmanPhysicsComponent.h"
#include "World.h"

PacmanPhysicsComponent::PacmanPhysicsComponent()
	: PhysicsComponent(collisionBox)
{
	this->collisionBox = CollisionBox(0, 0, PacmanGraphicsComponent::CHARACTER_WIDTH, PacmanGraphicsComponent::CHARACTER_HEIGHT);
}


PacmanPhysicsComponent::~PacmanPhysicsComponent()
{
}

void PacmanPhysicsComponent::update(GameObject &object, World &world)
{
	CollisionBox offsetCollisionBox = this->getCollisionBox();
	offsetCollisionBox.x += object.velocityX;
	offsetCollisionBox.y += object.velocityY;

	// check if pacman can take a turn in given direction
	if (world.CollisionBoxIsColidingWith(ID_TILE, offsetCollisionBox)) {
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

	this->shiftCollisionBox(object.x, object.y);
	world.resolveCollision(object);
}

void PacmanPhysicsComponent::receive(Message message, int objectId, GameObject &object)
{
	if (objectId == ID_TILE && message == COLLISION) {
		if (this->usedPreviousVelocity) {
			object.x -= this->previousVelocityX;
			object.y -= this->previousVelocityY;
		}
		else {
			object.x -= object.velocityX;
			object.y -= object.velocityY;
		}

		this->shiftCollisionBox(object.x, object.y);
	}
}

void PacmanPhysicsComponent::shiftCollisionBox(double x, double y)
{
	this->collisionBox.x = x;
	this->collisionBox.y = y;
}