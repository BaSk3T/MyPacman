#include "System.h"

System::System()
{
	this->init();
}


System::~System()
{
	this->quit();
}

void System::createWindow(char *name, int width, int height)
{
	SDL_Window *window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "Window could not initialize! Error: " << SDL_GetError() << std::endl;
	}

	this->windows.insert(std::make_pair(name, window));
}

void System::closeWindow(char *name)
{
	SDL_DestroyWindow(this->windows[name]);
}

SDL_Window * System::getWindow(char *name)
{
	return this->windows[name];
}

void System::delay(int milliseconds)
{
	SDL_Delay(milliseconds);
}

void System::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
	}
}

void System::quit()
{
	SDL_Quit();
}