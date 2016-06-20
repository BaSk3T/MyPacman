#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class SystemInput;
class SystemGraphics;
class World;

#pragma once
class GameObject
{
public:
	double x, y;
	double velocityX;
	double velocityY;
	int objectId;

	GameObject(int objectId, double x, double y, InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics);
	~GameObject();

	void update(World &world, SystemGraphics &graphics, SystemInput &input);
	void send(Message message, int objectId);

	InputComponent *input;
	PhysicsComponent *physics;
	GraphicsComponent *graphics;
};

