#include "GameTexture.h"
#include "CollisionBox.h"

#pragma once
class Character
{
public:
	Character(double x, double y, int maxFrames, int frameDelay, int width, int height);
	~Character();

	void increaseFrame();
	void shifCollisionBox();
	void fixAngle();

	double getX() const;
	void setX(double value);

	double getY() const;
	void setY(double value);

	bool getGoingRight() const;
	void setGoingRight(bool value);

	bool getGoingUp() const;
	void setGoingUp(bool value);

	bool getMovingHorizontal() const;
	void setMovingHorizontal(bool value);

	double getAngle() const;
	void setAngle(double value);

	int getFrame() const;

	CollisionBox getCollisionBox() const;

private:
	double x;
	double y;
	int frame;
	int maxFrames;
	int frameDelay;
	double angle;
	bool goingRight;
	bool goingUp;
	bool movingHorizontal;
	CollisionBox collisionBox;
};

