#include "SDL.h"
#include "CollisionBox.h"

#pragma once
class Food
{
public:
	Food(int x, int y, double collisionBoxX, double collisionBoxY, int width, int height);
	~Food();

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

	bool getIsEaten() const;
	void setIsEaten(bool value);

	CollisionBox getCollisionBox() const;

private:
	int x;
	int y;
	bool isEaten;
	CollisionBox collisionBox;
};

