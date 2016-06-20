#include "PacmanGraphicsComponent.h"
#include "CollisionBox.h"
#include "GameObject.h"

#pragma once
class PacmanPhysicsComponent : public PhysicsComponent
{
public:
	PacmanPhysicsComponent();
	~PacmanPhysicsComponent();

	void update(GameObject &object, World &world);
	void receive(Message message, int objectId, GameObject &object);
	
private:
	static const int CHARACTER_WIDTH = 24;
	static const int CHARACTER_HEIGHT = 24;
	static const int ID_TILE = 0;

	double previousVelocityX = 0;
	double previousVelocityY = 0;
	bool usedPreviousVelocity = false;

	void shiftCollisionBox(double x, double y);
};

