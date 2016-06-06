#include <iostream>
#include <SDL.h>

#pragma once
class System
{
public:
	System();
	~System();

	SDL_Window *createWindow(char *title, int width, int height);
	void closeWindow(SDL_Window *window);

private:
	void init();
	void quit();
};

