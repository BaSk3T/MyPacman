#include <iostream>
#include <map>
#include <SDL_ttf.h>

#pragma once
class SystemFont
{
public:
	SystemFont();
	~SystemFont();

	void loadFont(char *name, char *path, int size);
	TTF_Font * getFont(char *name);

private:
	std::map<std::string, TTF_Font*> fonts;

	void init();
	void quit();
};

