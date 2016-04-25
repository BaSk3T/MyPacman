#include "GameTexture.h"

#pragma once
class Character
{
public:
	Character(int x, int y, int maxFrames, int frameDelay, int width, int height);
	~Character();

	void increaseFrame();
	void shifCollisionBox();
	void fixAngle();

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

	bool getGoingRight() const;
	void setGoingRight(bool value);

	bool getGoingUp() const;
	void setGoingUp(bool value);

	bool getMovingHorizontal() const;
	void setMovingHorizontal(bool value);

	double getAngle() const;
	void setAngle(double value);

	int getFrame() const;

	SDL_Rect getCollisionBox() const;

private:
	int x;
	int y;
	int frame;
	int maxFrames;
	int frameDelay;
	double angle;
	bool goingRight;
	bool goingUp;
	bool movingHorizontal;
	SDL_Rect collisionBox;
};

