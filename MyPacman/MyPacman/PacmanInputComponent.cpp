#include "PacmanInputComponent.h"

PacmanInputComponent::PacmanInputComponent()
{
}


PacmanInputComponent::~PacmanInputComponent()
{
}

void PacmanInputComponent::update(GameObject &object, SystemInput &input)
{
	for (Uint16 i = 0; i < input.commands.size(); i++) {
		switch (input.commands[i])
		{
		case DIR_LEFT:
			object.velocityX = -VELOCITY;
			object.velocityY = 0;
			break;
		case DIR_UP:
			object.velocityX = 0;
			object.velocityY = -VELOCITY;
			break;
		case DIR_RIGHT:
			object.velocityX = VELOCITY;
			object.velocityY = 0;
			break;
		case DIR_DOWN:
			object.velocityX = 0;
			object.velocityY = VELOCITY;
			break;
		default:
			break;
		}
	}
}

void PacmanInputComponent::receive(int message, int objectId)
{

}