class GameObject;
class World;

#include "Component.h"
#include "CollisionBox.h"

#pragma once
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(CollisionBox &collisionBox) : collisionBox(collisionBox) {};
	virtual ~PhysicsComponent() {};
	virtual void update(GameObject &object, World &world) = 0;
	CollisionBox getCollisionBox() const { return this->collisionBox; }

protected:
	CollisionBox collisionBox;
};

