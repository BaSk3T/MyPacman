#include <iostream>

#pragma once
class CollisionBox
{
public:
	double x;
	double y;
	int width;
	int height;

	CollisionBox();
	CollisionBox(double x, double y, int width, int height);
	~CollisionBox();

	bool isInRangeOf(const CollisionBox other, unsigned int range) const;
};

