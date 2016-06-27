#include "GhostPhysicsComponent.h"
#include "World.h"

GhostPhysicsComponent::GhostPhysicsComponent()
{
	this->collisionBox = CollisionBox(0, 0, GhostPhysicsComponent::GHOST_WIDTH, GhostPhysicsComponent::GHOST_HEIGHT);
}

GhostPhysicsComponent::~GhostPhysicsComponent()
{
}

void GhostPhysicsComponent::update(GameObject &object, World &world)
{
	if (isCollidingWithTrail(object, world)) {
		this->foundTrail = true;
	}
	else {
		this->foundTrail = false;
	}

	if (!this->foundTrail) {
		int shouldSwitchDirection = (std::rand() % 1000) % 113;

		if (shouldSwitchDirection == 0) {
			this->switchDirection(object);
		}
	}

	this->takeTurnIfPossible(world, object);

	this->shiftCollisionBox(object.x, object.y);
	world.resolveCollision(object);
}

void GhostPhysicsComponent::receive(Message message, int objectId, GameObject &object)
{
	if (message == COLLISION && objectId == 0) {
		if (this->usedPreviousVelocity) {
			object.x -= this->previousVelocityX;
			object.y -= this->previousVelocityY;
		}
		else {
			object.x -= object.velocityX;
			object.y -= object.velocityY;
		}

		shiftCollisionBox(object.x, object.y);
		switchDirection(object);
	}
}

bool GhostPhysicsComponent::isCollidingWithTrail(GameObject &object, World &world)
{
	// starting from 1 because if pinky is colliding with last 1 there will be collision with pacman ( thus pacman is dead )
	for (Uint16 i = 1; i < world.trail.size(); i++) {

		if (world.checkCollision(this->collisionBox, world.trail[i])) {
			if (world.trail[i - 1].x > world.trail[i].x) {
				object.velocityX = VELOCITY;
				object.velocityY = 0;
			}
			else if (world.trail[i - 1].x < world.trail[i].x) {
				object.velocityX = -VELOCITY;
				object.velocityY = 0;
			}
			else if (world.trail[i - 1].y < world.trail[i].y) {
				object.velocityX = 0;
				object.velocityY = -VELOCITY;
			}
			else {
				object.velocityX = 0;
				object.velocityY = VELOCITY;
			}

			return true;
		}
	}

	return false;
}

void GhostPhysicsComponent::switchDirection(GameObject &object)
{
	if (object.velocityX != 0) {
		object.velocityX = 0;
		object.velocityY = (std::rand() % 2) == 1 ? VELOCITY : -VELOCITY;
	}
	else {
		object.velocityY = 0;
		object.velocityX = (std::rand() % 2) == 1 ? VELOCITY : -VELOCITY;
	}
}