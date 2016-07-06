#include "SystemGraphics.h"

SystemGraphics::SystemGraphics()
{
	this->init();
}


SystemGraphics::~SystemGraphics()
{
	for (std::map<std::string, GameTexture*>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {
		delete it->second;
	}

	this->quit();
}

void SystemGraphics::draw(char *name, int x, int y, int angle)
{
	GameTexture *sprite = this->sprites[name];

	SDL_Rect rect = { x, y, sprite->getWidth(), sprite->getHeight() };
	SDL_RenderCopyEx(renderer, sprite->texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void SystemGraphics::draw(char *name, int x, int y, Rectangle clip, int angle)
{
	SDL_Rect sdlClip = { clip.x, clip.y, clip.width, clip.height };
	SDL_Rect rect = { x, y, clip.width, clip.height };

	SDL_RenderCopyEx(renderer, this->sprites[name]->texture, &sdlClip, &rect, angle, NULL, SDL_FLIP_NONE);

}

void SystemGraphics::setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 a)
{
	SDL_SetRenderDrawColor(this->renderer, red, green, blue, a);
}

void SystemGraphics::clear()
{
	SDL_RenderClear(this->renderer);
}

void SystemGraphics::present()
{
	SDL_RenderPresent(this->renderer);
}

void SystemGraphics::createSprite(std::string name, char *path)
{
	// is there already a sprite with that name
	if (this->sprites.count(name)) {
		std::cout << "Sprite with name " << name << " already exists!" << std::endl;
		return;
	}

	GameTexture *sprite = new GameTexture();
	sprite->loadFromFile(path, this->renderer);

	this->sprites.insert(std::make_pair(name, sprite));
}

void SystemGraphics::createTextSprite(std::string name)
{
	// is there already a sprite with that name
	if (this->sprites.count(name)) {
		std::cout << "Sprite with name " << name << " already exists!" << std::endl;
		return;
	}

	GameTexture *sprite = new GameTexture();
	this->sprites.insert(std::make_pair(name, sprite));
}

void SystemGraphics::updateTextSprite(std::string name, std::string textureText, TTF_Font *font)
{
	SDL_Color color = { 0, 255, 0, 255 };
	this->sprites[name]->loadFromRenderedText(textureText, color, font, this->renderer);
}

void SystemGraphics::init()
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "SDL_image could not initialize! Error: " << IMG_GetError() << std::endl;
	}
}

void SystemGraphics::quit()
{
	IMG_Quit();
}

void SystemGraphics::initRenderer(SDL_Window *window)
{
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (this->renderer == NULL) {
		std::cout << "SDL_Renderer couldn't not initialize! Error: " << SDL_GetError() << std::endl;
	}
	else {
		SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
}