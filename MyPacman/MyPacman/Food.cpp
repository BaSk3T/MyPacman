#include "Food.h"



Food::Food(int x, int y, double collisionBoxX, double collisionBoxY, int width, int height)
{
	this->x = x;
	this->y = y;
	this->isEaten = false;

	this->collisionBox = CollisionBox(collisionBoxX, collisionBoxY, width, height);
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

CollisionBox Food::getCollisionBox() const
{
	return this->collisionBox;
}