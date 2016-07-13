#include "PacmanInputComponent.h"

const double PacmanInputComponent::VELOCITY = 1.5;

PacmanInputComponent::PacmanInputComponent()
{
}


PacmanInputComponent::~PacmanInputComponent()
{
}

void PacmanInputComponent::update(GameObject &object, SystemInput &input)
{
	bool changedDirection = false;

	for (Uint16 i = 0; i < input.commands.size(); i++) {
		switch (input.commands[i])
		{
		case DIR_LEFT:
			object.velocityX = -VELOCITY;
			object.velocityY = 0;
			changedDirection = true;
			break;
		case DIR_UP:
			object.velocityX = 0;
			object.velocityY = -VELOCITY;
			changedDirection = true;
			break;
		case DIR_RIGHT:
			object.velocityX = VELOCITY;
			object.velocityY = 0;
			changedDirection = true;
			break;
		case DIR_DOWN:
			object.velocityX = 0;
			object.velocityY = VELOCITY;
			changedDirection = true;
			break;
		default:
			break;
		}
	}

	if (changedDirection) {
		object.send(STATE_CHANGE, object);
	}
}

void PacmanInputComponent::receive(Message message, GameObject &other, GameObject &object)
{

}