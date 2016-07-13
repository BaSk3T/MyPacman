#include "FoodPhysicsComponent.h"
#include "World.h"


FoodPhysicsComponent::FoodPhysicsComponent(CollisionBox collisionBox)
	: PhysicsComponent(collisionBox)
{
}

FoodPhysicsComponent::~FoodPhysicsComponent()
{
}

void FoodPhysicsComponent::update(GameObject &object, World &world)
{
}

void FoodPhysicsComponent::receive(Message message, GameObject &other, GameObject &object)
{
}