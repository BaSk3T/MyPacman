#include "GameObject.h"
#include "CollisionBox.h"

#pragma once
class TilePhysicsComponent : public PhysicsComponent
{
public:
	TilePhysicsComponent(CollisionBox collisionBox);
	~TilePhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(int message, int objectId);

	CollisionBox getCollisionBox() const;
private:
	CollisionBox collisionBox;
};

