#include <iostream>
#include <map>
#include <SDL.h>

#pragma once
class System
{
public:
	System();
	~System();

	void createWindow(char *name, int width, int height);
	void closeWindow(char *name);
	SDL_Window * getWindow(char *name);
	void delay(int milliseconds);

private:
	std::map<std::string, SDL_Window*> windows;

	void init();
	void quit();
};

