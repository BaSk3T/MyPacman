#include "InputComponent.h"

#pragma once
class PortalInputComponent : public InputComponent
{
public:
	PortalInputComponent();
	~PortalInputComponent();

	void update(GameObject &object, SystemInput &input);
	void receive(Message message, GameObject &other, GameObject &object);
};

