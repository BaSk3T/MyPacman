#include "Food.h"



Food::Food(int x, int y, int collisionBoxX, int collisionBoxY, int width, int height)
{
	this->x = x;
	this->y = y;
	this->isEaten = false;

	this->collisionBox.x = collisionBoxX;
	this->collisionBox.y = collisionBoxY;
	this->collisionBox.w = width;
	this->collisionBox.h = height;
}

Food::~Food()
{
}

int Food::getX() const
{
	return this->x;
}

void Food::setX(int value)
{
	this->x = value;
}

int Food::getY() const
{
	return this->y;
}

void Food::setY(int value)
{
	this->y = value;
}

bool Food::getIsEaten() const
{
	return this->isEaten;
}

void Food::setIsEaten(bool value)
{
	this->isEaten = value;
}

SDL_Rect Food::getCollisionBox() const
{
	return this->collisionBox;
}