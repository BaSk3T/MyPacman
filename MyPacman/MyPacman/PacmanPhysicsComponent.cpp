#include "PacmanPhysicsComponent.h"



PacmanPhysicsComponent::PacmanPhysicsComponent()
{
}


PacmanPhysicsComponent::~PacmanPhysicsComponent()
{
}

void PacmanPhysicsComponent::update(GameObject &object, World &world)
{
	object.x += object.velocityX;
	object.y += object.velocityY;

	this->collisionBox.x = object.x;
	this->collisionBox.y = object.y;
}

void PacmanPhysicsComponent::receive(int message, int objectId)
{

}