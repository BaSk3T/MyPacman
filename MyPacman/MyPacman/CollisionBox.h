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
};

