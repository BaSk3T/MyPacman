#include <iostream>
#include <string>
#include <map>
#include <SDL_image.h>
#include "GameTexture.h"
#include "Rectangle.h"

#pragma once
class SystemGraphics
{
public:
	SystemGraphics();
	~SystemGraphics();

	void initRenderer(SDL_Window *window);
	void createSprite(std::string name, char *path);
	void draw(char *name, int x, int y, int angle = 0);
	void draw(char *name, int x, int y, Rectangle clip, int angle = 0);
	void setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 a);
	void clear();
	void present();

private:
	SDL_Renderer *renderer;
	std::map<std::string, GameTexture*> sprites;

	void init();
	void quit();
};

