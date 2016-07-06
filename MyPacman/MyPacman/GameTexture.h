#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#pragma once
class GameTexture
{
public:
	SDL_Texture *texture;

	GameTexture();
	~GameTexture();

	bool loadFromFile(char* path, SDL_Renderer *renderer);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font, SDL_Renderer *renderer);

	int getWidth() const;
	int getHeight() const;

private:
	int width;
	int height;

	void free();
};

