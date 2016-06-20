#include "SystemGraphics.h"
#include "GameObject.h"
#include "Rectangle.h"

#pragma once
class PacmanGraphicsComponent : public GraphicsComponent
{
public:
	static const int CHARACTER_WIDTH = 24;
	static const int CHARACTER_HEIGHT = 24;

	PacmanGraphicsComponent();
	~PacmanGraphicsComponent();

	void update(GameObject &object, SystemGraphics &graphics);
	void receive(Message message, int objectId, GameObject &object);

private:
	static Rectangle clips[];
	static const int FRAME_DELAY = 5;
	static const int MAX_FRAMES = 3;

	int frame = 0;
	int angle = 0;
	bool changeAngle = true;

	void fixAngle(GameObject &object);
};

