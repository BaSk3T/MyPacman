#include "GameObject.h"
#include "SystemGraphics.h"

#pragma once
class FoodGraphicsComponent : public GraphicsComponent
{
public:
	FoodGraphicsComponent();
	~FoodGraphicsComponent();

	void update(GameObject &object, SystemGraphics &graphics);
	void receive(int message, int objectId);

private:
	int eaten = 0;
	bool draw = true;
};

