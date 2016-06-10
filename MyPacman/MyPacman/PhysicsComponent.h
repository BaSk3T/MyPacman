class GameObject;
class World;

#include "Component.h"

#pragma once
class PhysicsComponent : public Component
{
public:
	virtual ~PhysicsComponent() {};
	virtual void update(GameObject &object, World &world) = 0;
};

