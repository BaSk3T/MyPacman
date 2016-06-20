#include "GameObject.h"
#include "CollisionBox.h"

#pragma once
class TilePhysicsComponent : public PhysicsComponent
{
public:
	TilePhysicsComponent(CollisionBox collisionBox);
	~TilePhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(Message message, int objectId, GameObject &object);
};

