#include "GameTile.h"

GameTile::GameTile()
{
}

GameTile::GameTile(double x, double y, int width, int height, int tileType)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = tileType;

	this->collisionBox = CollisionBox(x, y, width, height);
}


GameTile::~GameTile()
{
}

double GameTile::getX() const
{
	return this->x;
}

void GameTile::setX(double value)
{
	this->x = value;
}

double GameTile::getY() const
{
	return this->y;
}

void GameTile::setY(double value)
{
	this->y = value;
}

int GameTile::getWidth() const
{
	return this->width;
}

int GameTile::getHeight() const
{
	return this->height;
}

int GameTile::getType() const
{
	return this->type;
}

CollisionBox GameTile::getCollisionBox() const
{
	return this->collisionBox;
}