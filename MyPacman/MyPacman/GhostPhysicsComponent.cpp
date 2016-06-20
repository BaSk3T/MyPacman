#include "GhostPhysicsComponent.h"

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
}

void GhostPhysicsComponent::receive(Message message, int objectId, GameObject &object)
{

}

void GhostPhysicsComponent::switchDirection(GameObject &object)
{

}

void GhostPhysicsComponent::shiftCollisionBox(double x, double y)
{
	this->collisionBox.x = x;
	this->collisionBox.y = y;
}