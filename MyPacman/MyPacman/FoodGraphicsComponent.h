#include "GameObject.h"
#include "SystemGraphics.h"

#pragma once
class FoodGraphicsComponent : public GraphicsComponent
{
public:
	FoodGraphicsComponent();
	~FoodGraphicsComponent();

	void update(GameObject &object, SystemGraphics &graphics);
	void receive(Message message, GameObject &other, GameObject &object);

private:
	static const int ID_PACMAN = 2;
	bool draw = true;
};

