class SystemInput;

#include "InputComponent.h"

#pragma once
class TileInputComponent : public InputComponent
{
public:
	TileInputComponent();
	~TileInputComponent();

	void update(GameObject &object, SystemInput &input);
	void receive(Message message, int objectId, GameObject &object);
};

