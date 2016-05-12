#include "GameTexture.h"

#pragma once
class GameTile
{
public:
	GameTile::GameTile();
	GameTile(int x, int y, int width, int height, int tileType);
	~GameTile();

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

	int getWidth() const;
	int getHeight() const;
	int getType() const;
	SDL_Rect getCollisionBox() const;

private:
	int x;
	int y;
	int width;
	int height;
	SDL_Rect collisionBox;
	int type;
};

