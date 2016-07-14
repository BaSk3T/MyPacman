#include "GraphicsComponent.h"

#pragma once
class PortalGraphicsComponent : public GraphicsComponent
{
public:
	PortalGraphicsComponent();
	~PortalGraphicsComponent();

	void update(GameObject &object, SystemGraphics &graphics);
	void receive(Message message, GameObject &other, GameObject &object);
};

