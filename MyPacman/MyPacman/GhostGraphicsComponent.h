#include "GraphicsComponent.h"
#include "SystemGraphics.h"
#include "Rectangle.h"
#include "GameObject.h"

#pragma once
class GhostGraphicsComponent : public GraphicsComponent
{
public:
	GhostGraphicsComponent();
	~GhostGraphicsComponent();

	void update(GameObject &object, SystemGraphics &graphics);
	void receive(Message message, int objectId, GameObject &object);
	void determineDirection(GameObject &object);

private:
	static Rectangle clips[4][2];
	static const int FRAME_DELAY = 5;
	static const int MAX_FRAMES = 2;

	int frame = 0;
	int direction = 0;
};
