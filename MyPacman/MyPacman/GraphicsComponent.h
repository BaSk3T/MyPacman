class SystemGraphics;
class GameObject;

#include "Component.h"

#pragma once
class GraphicsComponent : public Component
{
public:
	virtual ~GraphicsComponent() {};
	virtual void update(GameObject &object, SystemGraphics &graphics) = 0;
};

