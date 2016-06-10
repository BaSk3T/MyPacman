#include "FoodGraphicsComponent.h"

FoodGraphicsComponent::FoodGraphicsComponent()
{
}


FoodGraphicsComponent::~FoodGraphicsComponent()
{
}

void FoodGraphicsComponent::update(GameObject &object, SystemGraphics &graphics)
{
	if (draw) {
		graphics.draw("food", (int)object.x, (int)object.y);
	}
}

void FoodGraphicsComponent::receive(int message, int objectId)
{
	if (message == this->eaten) {
		this->draw = false;
	}
}