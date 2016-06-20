class SystemInput;

#include "InputComponent.h"

#pragma once
class FoodInputComponent : public InputComponent
{
public:
	FoodInputComponent();
	~FoodInputComponent();

	void update(GameObject &object, SystemInput &input);
	void receive(Message message, int objectId, GameObject &object);
};

