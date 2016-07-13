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

void TilePhysicsComponent::receive(Message message, GameObject &other, GameObject &object)
{
}