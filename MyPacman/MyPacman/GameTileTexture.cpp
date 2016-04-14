#include "GameTileTexture.h"

GameTileTexture::GameTileTexture()
{
}

GameTileTexture::GameTileTexture(int x, int y, int width, int height, int tileType)
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


GameTileTexture::~GameTileTexture()
{
}

void GameTileTexture::render(SDL_Renderer *renderer, GameTexture *tilesTexture, SDL_Rect tiles[])
{
	tilesTexture->render(this->x, this->y, renderer, &tiles[this->type]);
}

int GameTileTexture::getX() const
{
	return this->x;
}

void GameTileTexture::setX(int value)
{
	this->x = value;
}

int GameTileTexture::getY() const
{
	return this->y;
}

void GameTileTexture::setY(int value)
{
	this->y = value;
}

int GameTileTexture::getWidth() const
{
	return this->width;
}

int GameTileTexture::getHeight() const
{
	return this->height;
}

int GameTileTexture::getType() const
{
	return this->type;
}

SDL_Rect GameTileTexture::getCollisionBox() const
{
	return this->collisionBox;
}