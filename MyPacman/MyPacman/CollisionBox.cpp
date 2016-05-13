#include "CollisionBox.h"

CollisionBox::CollisionBox()
{
}

CollisionBox::CollisionBox(double x, double y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

CollisionBox::~CollisionBox()
{
}
