#include "InputComponent.h"

#pragma once
class GhostInputComponent : public InputComponent
{
public:
	GhostInputComponent();
	~GhostInputComponent();

	void update(GameObject &object, SystemInput &input);
	void receive(Message message, int objectId, GameObject &object);
};

