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

void FoodGraphicsComponent::receive(Message message, GameObject &other, GameObject &object)
{
	if (other.objectId == ID_PACMAN && message == COLLISION) {
		this->draw = false;
	}
}