#include "PhysicsComponent.h"
#include "CollisionBox.h"

#pragma once
class FoodPhysicsComponent : public PhysicsComponent
{
public:
	FoodPhysicsComponent(CollisionBox collisionBox);
	~FoodPhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(int message, int objectId);

	CollisionBox getCollisionBox() const;

private:
	CollisionBox collisionBox;
};

