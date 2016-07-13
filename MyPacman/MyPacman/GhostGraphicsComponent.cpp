#include "GhostGraphicsComponent.h"

Rectangle GhostGraphicsComponent::clips[4][2] =  {
		{ { 0, 0, 24, 24 },{ 0, 24, 24, 24 } },
		{ { 24, 0, 24, 24 },{ 24, 24, 24, 24 } },
		{ { 48, 0, 24, 24 },{ 48, 24, 24, 24 } },
		{ { 72, 0, 24, 24 },{ 72, 24, 24, 24 } }
	};

GhostGraphicsComponent::GhostGraphicsComponent(char *textureName)
	: textureName(textureName)
{
}

GhostGraphicsComponent::~GhostGraphicsComponent()
{
}

void GhostGraphicsComponent::update(GameObject &object, SystemGraphics &graphics)
{
	if (this->shouldDetermineDirection) {
		this->determineDirection(object);
	}

	graphics.draw(this->textureName, (int)object.x, (int)object.y, this->clips[this->direction][this->frame / FRAME_DELAY]);

	this->frame++;

	if (this->frame / FRAME_DELAY >= MAX_FRAMES) {
		this->frame = 0;
	}
}

void GhostGraphicsComponent::receive(Message message, GameObject &other, GameObject &object)
{
	if (message == STATE_CHANGE && other.objectId == object.objectId) {
		this->shouldDetermineDirection = false;
	}

	if (message == STATE_ORIGINAL && other.objectId == object.objectId) {
		this->shouldDetermineDirection = true;
	}
}

void GhostGraphicsComponent::determineDirection(GameObject &object)
{
	if (object.velocityX < 0 && object.velocityY == 0) { // left
		this->direction = 0;
	}
	else if (object.velocityX == 0 && object.velocityY < 0) { // up
		this->direction = 1;
	}
	else if (object.velocityX > 0 && object.velocityY == 0) { // right
		this->direction = 2;
	}
	else {
		this->direction = 3; // down
	}
}