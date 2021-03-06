#include "GameObject.h"
#include "Rectangle.h"
#include "SystemGraphics.h"

#pragma once
class TileGraphicsComponent : public GraphicsComponent
{
public:
	TileGraphicsComponent(Rectangle clip);
	~TileGraphicsComponent();

	void update(GameObject &object, SystemGraphics &graphics);
	void receive(Message message, GameObject &other, GameObject &object);
private:
	Rectangle clip;
};

