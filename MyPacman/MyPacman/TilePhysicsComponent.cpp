#include "TilePhysicsComponent.h"

TilePhysicsComponent::TilePhysicsComponent(CollisionBox collisionBox) : collisionBox(collisionBox)
{
}

TilePhysicsComponent::~TilePhysicsComponent()
{
}

void TilePhysicsComponent::update(GameObject &object, World &world)
{
}

void TilePhysicsComponent::receive(int message, int objectId)
{
}

CollisionBox TilePhysicsComponent::getCollisionBox() const
{
	return this->collisionBox;
}