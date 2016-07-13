#include "PacmanPhysicsComponent.h"
#include "World.h"

PacmanPhysicsComponent::PacmanPhysicsComponent()
{
	this->collisionBox = CollisionBox(0, 0, PacmanGraphicsComponent::CHARACTER_WIDTH, PacmanGraphicsComponent::CHARACTER_HEIGHT);
}


PacmanPhysicsComponent::~PacmanPhysicsComponent()
{
}

void PacmanPhysicsComponent::update(GameObject &object, World &world)
{
	if (this->takeTurnIfPossible(world, object)) {
		this->changedDirection = false;
	}

	if (!world.checkCollision(this->collisionBox, world.trail.front())) {
		world.trail.push_front(this->collisionBox);
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

	if (objectId == object.objectId && message == STATE_CHANGE) {
		this->changedDirection = true;
	}
}