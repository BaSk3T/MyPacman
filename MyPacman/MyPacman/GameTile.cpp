#include "GameTile.h"

GameTile::GameTile()
{
}

GameTile::GameTile(int x, int y, int width, int height, int tileType)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = tileType;

	this->collisionBox.x = x;
	this->collisionBox.y = y;
	this->collisionBox.w = width;
	this->collisionBox.h = height;
}


GameTile::~GameTile()
{
}

int GameTile::getX() const
{
	return this->x;
}

void GameTile::setX(int value)
{
	this->x = value;
}

int GameTile::getY() const
{
	return this->y;
}

void GameTile::setY(int value)
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

SDL_Rect GameTile::getCollisionBox() const
{
	return this->collisionBox;
}