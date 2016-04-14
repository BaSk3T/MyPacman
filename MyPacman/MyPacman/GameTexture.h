#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#pragma once
class GameTexture
{
private:
	SDL_Texture *texture;

	int width;
	int height;

public:
	GameTexture();
	~GameTexture();

	bool loadFromFile(char* path, SDL_Renderer *renderer);

	void free();

	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clipRect = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() const;
	int getHeight() const;
};

