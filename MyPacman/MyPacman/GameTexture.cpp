#include "GameTexture.h"

GameTexture::GameTexture()
{
}

GameTexture::~GameTexture()
{
	this->free();
}

void GameTexture::free()
{
	if (this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
		this->width = 0;
		this->height = 0;
	}
}

bool GameTexture::loadFromFile(char *path, SDL_Renderer *renderer)
{
	this->free();

	SDL_Surface *loadedImage = IMG_Load(path);
	SDL_Texture *newTexture = nullptr;

	if (loadedImage == NULL) {
		std::cout << "Unable to load image! Error: " << SDL_GetError() << std::endl;
	}
	else {
		//SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 255, 21));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedImage);

		if (newTexture == NULL) {
			std::cout << "Couldn't load texture from " << path << " Error: " << SDL_GetError() << std::endl;
		}
		else {
			this->width = loadedImage->w;
			this->height = loadedImage->h;
		}

		SDL_FreeSurface(loadedImage);

		this->texture = newTexture;
	}

	return newTexture != NULL;
}

bool GameTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font, SDL_Renderer *renderer)
{
	this->free();

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	SDL_Texture *newTexture = nullptr;

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			this->width = textSurface->w;
			this->height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
		this->texture = newTexture;
	}

	return newTexture != NULL;
}

int GameTexture::getHeight() const
{
	return this->height;
}

int GameTexture::getWidth() const
{
	return this->width;
}