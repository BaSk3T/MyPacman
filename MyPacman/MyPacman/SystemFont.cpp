#include "SystemFont.h"

SystemFont::SystemFont()
{
	this->init();
}

SystemFont::~SystemFont()
{
	for (std::map<std::string, TTF_Font*>::iterator it = this->fonts.begin(); it != this->fonts.end(); ++it) {
		TTF_CloseFont(it->second);
	}

	this->quit();
}

void SystemFont::loadFont(char *name, char *path, int size)
{
	TTF_Font *font = TTF_OpenFont(path, size);

	if (font == NULL)
	{
		printf("Failed to load %s font! SDL_ttf Error: %s\n", path, TTF_GetError());
		return;
	}
	
	// is there already a sprite with that name
	if (this->fonts.count(name)) {
		std::cout << "Font with name " << name << " already exists!" << std::endl;
		return;
	}

	this->fonts.insert(std::make_pair(name, font));
}

TTF_Font *SystemFont::getFont(char *name)
{
	return this->fonts[name];
}

void SystemFont::init()
{
	if (TTF_Init() < 0) {
		std::cout << "TTF could not initialize! Error: " << TTF_GetError() << std::endl;
	}
}

void SystemFont::quit()
{
	TTF_Quit();
}