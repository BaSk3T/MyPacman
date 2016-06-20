#include "TilePhysicsComponent.h"

TilePhysicsComponent::TilePhysicsComponent(CollisionBox collisionBox)
	: PhysicsComponent(collisionBox)
{
}

TilePhysicsComponent::~TilePhysicsComponent()
{
}

void TilePhysicsComponent::update(GameObject &object, World &world)
{
}

void TilePhysicsComponent::receive(Message message, int objectId, GameObject &object)
{
}