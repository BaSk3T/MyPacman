class GameObject;
class SystemInput;

#include "Component.h"

#pragma once
class InputComponent : public Component
{
public:
	virtual ~InputComponent() {};
	virtual void update(GameObject &object, SystemInput &input) = 0;
};

