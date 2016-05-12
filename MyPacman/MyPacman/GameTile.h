#include "GameTexture.h"
#include "CollisionBox.h"

#pragma once
class GameTile
{
public:
	GameTile::GameTile();
	GameTile(double x, double y, int width, int height, int tileType);
	~GameTile();

	double getX() const;
	void setX(double value);

	double getY() const;
	void setY(double value);

	int getWidth() const;
	int getHeight() const;
	int getType() const;
	CollisionBox getCollisionBox() const;

private:
	double x;
	double y;
	int width;
	int height;
	CollisionBox collisionBox;
	int type;
};

