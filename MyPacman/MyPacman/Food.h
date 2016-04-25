#include "SDL.h"

#pragma once
class Food
{
public:
	Food(int x, int y, int collisionBoxX, int collisionBoxY, int width, int height);
	~Food();

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

	bool getIsEaten() const;
	void setIsEaten(bool value);

	SDL_Rect getCollisionBox() const;

private:
	int x;
	int y;
	bool isEaten;
	SDL_Rect collisionBox;
};

