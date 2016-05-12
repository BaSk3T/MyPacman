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

bool CollisionBox::isInRangeOf(const CollisionBox other, unsigned int range) const
{
	int differenceInX = (int)std::abs(this->x - other.x);
	int differenceInY = (int)std::abs(this->y - other.y);

	bool isInRange = false;

	if (differenceInX <= range && differenceInY <= range) {
		isInRange = true;
	}

	return isInRange;
}
