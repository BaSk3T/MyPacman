#include "GhostPhysicsComponent.h"
#include "World.h"

GhostPhysicsComponent::GhostPhysicsComponent()
	: PhysicsComponent(collisionBox)
{
	this->collisionBox = CollisionBox(0, 0, GhostPhysicsComponent::GHOST_WIDTH, GhostPhysicsComponent::GHOST_HEIGHT);
}

GhostPhysicsComponent::~GhostPhysicsComponent()
{
}

void GhostPhysicsComponent::update(GameObject &object, World &world)
{
	int shouldSwitchDirection = (std::rand() % 1000) % 237;

	if (shouldSwitchDirection == 0) {
		this->switchDirection(object);
	}

	object.x += object.velocityX;
	object.y += object.velocityY;

	this->shiftCollisionBox(object.x, object.y);
	world.resolveCollision(object);
}

void GhostPhysicsComponent::receive(Message message, int objectId, GameObject &object)
{
	if (message == COLLISION && objectId == 0) {
		object.x -= object.velocityX;
		object.y -= object.velocityY;

		shiftCollisionBox(object.x, object.y);
		switchDirection(object);
	}
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

void GhostPhysicsComponent::shiftCollisionBox(double x, double y)
{
	this->collisionBox.x = x;
	this->collisionBox.y = y;
}