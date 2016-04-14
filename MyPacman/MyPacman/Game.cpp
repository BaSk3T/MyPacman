#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameTileTexture.h"

SDL_Window *init(char *title, int width, int height);
SDL_Renderer *initRenderer(SDL_Window *window);
int loadTiles(char *mapPath, GameTileTexture *tiles[], int numberOfTiles);
void loadTileClips(SDL_Rect tilesClips[]);

short const WINDOW_HEIGHT = 640;
short const WINDOW_WIDTH = 860;
short const NUMBER_OF_TILE_TYPES = 1;
short const NUMBER_OF_TILES = 100;
short const TILE_WIDTH = 32;
short const TILE_HEIGHT = 32;
short const MAP_WIDTH = 320;

SDL_Rect tilesClips[NUMBER_OF_TILE_TYPES];

enum TileType
{
	BLACK_BOX = 0
};

int main(int argc, char ** argv)
{
	SDL_Window *window = init("MyPacman", WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Renderer *renderer = initRenderer(window);

	SDL_Event ev;
	int delay = 1000 / 60;
	bool hasQuit = false;

	GameTexture *tilesTexture = new GameTexture();
	tilesTexture->loadFromFile("tiles.png", renderer);

	GameTileTexture *tiles[NUMBER_OF_TILES];

	int numberOfLoadedTiles = loadTiles("level.map", tiles, NUMBER_OF_TILES);
	loadTileClips(tilesClips);

	while (!hasQuit) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				hasQuit = true;
			}
		}

		SDL_Delay(delay);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		for (int i = 0; i < numberOfLoadedTiles; i++) {
			tiles[i]->render(renderer, tilesTexture, tilesClips);
		}

		SDL_RenderPresent(renderer);
	}

	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete tilesTexture;

	for (int i = 0; i < numberOfLoadedTiles; i++) {
		delete tiles[i];
	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}

SDL_Window *init(char *title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
	}

	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "Window could not initialize! Error: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_image could not initialize! Error: " << IMG_GetError() << std::endl;
	}

	return window;
}

SDL_Renderer *initRenderer(SDL_Window *window)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		std::cout << "SDL_Renderer couldn't not initialize! Error: " << SDL_GetError() << std::endl;
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	return renderer;
}

int loadTiles(char *mapPath, GameTileTexture *tiles[], int numberOfTiles)
{
	int x = 0;
	int y = 0;

	int indexOfTile = 0;

	std::ifstream map(mapPath);

	if (!map.is_open()) {
		std::cout << "Unable to load map file!" << std::endl;
	}
	else {
		for (short i = 0; i < numberOfTiles; i++) {
			int tyleType = -1;

			map >> tyleType;

			if (map.fail()) {
				std::cout << "Error loading map: Unexpected end of file!" << std::endl;
			}

			if (1 <= tyleType && tyleType <= NUMBER_OF_TILE_TYPES) {
				tiles[indexOfTile] = new GameTileTexture(x, y, TILE_WIDTH, TILE_HEIGHT, tyleType - 1);
				indexOfTile++;
			}
			else if (tyleType != 0){
				std::cout << "Error loading map: Unrecognized tyle type!" << std::endl;
			}

			x += TILE_WIDTH;

			if (x >= MAP_WIDTH) {
				x = 0;

				y += TILE_HEIGHT;
			}
		}
	}

	map.close();

	return indexOfTile;
}

void loadTileClips(SDL_Rect tilesClips[])
{
	tilesClips[BLACK_BOX].x = 0;
	tilesClips[BLACK_BOX].y = 0;
	tilesClips[BLACK_BOX].w = TILE_WIDTH;
	tilesClips[BLACK_BOX].h = TILE_HEIGHT;
}