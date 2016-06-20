#include "PacmanGraphicsComponent.h"

Rectangle PacmanGraphicsComponent::clips[]  = {
	{ 0, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT },
	{ 24, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT },
	{ 48, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT },
};

PacmanGraphicsComponent::PacmanGraphicsComponent()
{
}

PacmanGraphicsComponent::~PacmanGraphicsComponent()
{
}

void PacmanGraphicsComponent::update(GameObject &object, SystemGraphics &graphics)
{
	if (this->changeAngle) {
		this->fixAngle(object);
	}

	graphics.draw("pacman", (int)object.x, (int)object.y, this->clips[this->frame / FRAME_DELAY], this->angle);

	this->frame++;

	if (this->frame / FRAME_DELAY >= MAX_FRAMES) {
		this->frame = 0;
	}
}

void PacmanGraphicsComponent::receive(Message message, int objectId, GameObject &object)
{
	if (message == STATE_CHANGE && objectId == object.objectId) {
		this->changeAngle = false;
	}

	if (message == STATE_ORIGINAL && objectId == object.objectId) {
		this->changeAngle = true;
	}
}

void PacmanGraphicsComponent::fixAngle(GameObject &object)
{
	if (object.velocityX < 0 && object.velocityY == 0) {
		this->angle = 180; // facing left
	}
	else if (object.velocityX == 0 && object.velocityY > 0) {
		this->angle = 90; // facing down
	}
	else if (object.velocityX == 0 && object.velocityY < 0) {
		this->angle = 270; // facing up
	}
	else {
		this->angle = 0; // facing right
	}
}