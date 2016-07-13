#include "MovingPhysicsComponent.h"

#pragma once
class PacmanPhysicsComponent : public MovingPhysicsComponent
{
public:
	PacmanPhysicsComponent();
	~PacmanPhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(Message message, GameObject &other, GameObject &object);
	
private:
	static const int CHARACTER_WIDTH = 24;
	static const int CHARACTER_HEIGHT = 24;
};

