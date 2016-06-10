#include "FoodPhysicsComponent.h"
#include "World.h"


FoodPhysicsComponent::FoodPhysicsComponent(CollisionBox collisionBox)
	: collisionBox(collisionBox)
{
}

FoodPhysicsComponent::~FoodPhysicsComponent()
{
}

void FoodPhysicsComponent::update(GameObject &object, World &world)
{
}

void FoodPhysicsComponent::receive(int message, int objectId)
{
}

CollisionBox FoodPhysicsComponent::getCollisionBox() const
{
	return this->collisionBox;
}