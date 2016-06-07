#include "System.h"

System::System()
{
	this->init();
}


System::~System()
{
	this->quit();
}

SDL_Window * System::createWindow(char *title, int width, int height)
{
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "Window could not initialize! Error: " << SDL_GetError() << std::endl;
	}

	return window;
}

void System::closeWindow(SDL_Window *window)
{
	SDL_DestroyWindow(window);
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