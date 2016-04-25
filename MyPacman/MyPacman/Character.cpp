#include "Character.h"



Character::Character(int x, int y, int maxFrames, int frameDelay, int width, int height)
{
	this->x = x;
	this->y = y;
	this->collisionBox = { x, y, width, height };
	this->maxFrames = maxFrames;
	this->frameDelay = frameDelay;
	this->frame = 0;
	this->goingRight = true;
	this->goingUp = false;
	this->movingHorizontal = true;
}

Character::~Character()
{
}

void Character::updateFrame(GameTexture *texture, SDL_Renderer *renderer, SDL_Rect characterClips[])
{
	double angle = 0;

	// if none is true angle is 0 ( facing right )
	if (!goingRight && movingHorizontal) {
		angle = 180; // facing left
	}
	else if (!goingUp && !movingHorizontal) {
		angle = 90; // facing down
	}
	else if (goingUp && !movingHorizontal) {
		angle = 270; // facing up
	}

	texture->render(this->x, this->y, renderer, &characterClips[this->frame / frameDelay], angle);

	this->frame++;

	if (this->frame / this->frameDelay >= this->maxFrames) {
		this->frame = 0;
	}
}

void Character::shifCollisionBox()
{
	this->collisionBox.x = this->x;
	this->collisionBox.y = this->y;
}

int Character::getX() const
{
	return this->x;
}

void Character::setX(int value)
{
	this->x = value;
}

int Character::getY() const
{
	return this->y;
}

void Character::setY(int value)
{
	this->y = value;
}

bool Character::getGoingRight() const
{
	return this->goingRight;
}

void Character::setGoingRight(bool value)
{
	this->goingRight = value;
}

bool Character::getGoingUp() const
{
	return this->goingUp;
}

void Character::setGoingUp(bool value)
{
	this->goingUp = value;
}

bool Character::getMovingHorizontal() const
{
	return this->movingHorizontal;
}

void Character::setMovingHorizontal(bool value)
{
	this->movingHorizontal = value;
}

SDL_Rect Character::getCollisionBox() const
{
	return this->collisionBox;
}