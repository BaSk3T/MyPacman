#include "SystemInput.h"
#include "GameObject.h"

#pragma once
class PacmanInputComponent : public InputComponent
{
public:
	PacmanInputComponent();
	~PacmanInputComponent();

	void update(GameObject &object, SystemInput &input);
	void receive(int message, int objectId);

private:
	static const int VELOCITY = 2;
};

