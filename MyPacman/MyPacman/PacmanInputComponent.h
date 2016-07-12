#include "SystemInput.h"
#include "GameObject.h"

#pragma once
class PacmanInputComponent : public InputComponent
{
public:
	PacmanInputComponent();
	~PacmanInputComponent();

	void update(GameObject &object, SystemInput &input);
	void receive(Message message, int objectId, GameObject &object);

private:
	static const double VELOCITY;
};

