#include "PhysicsComponent.h"

#pragma once
class PortalPhysicsComponent : public PhysicsComponent
{
public:
	PortalPhysicsComponent(CollisionBox collisionBox);
	~PortalPhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(Message message, GameObject &other, GameObject &object);
};

