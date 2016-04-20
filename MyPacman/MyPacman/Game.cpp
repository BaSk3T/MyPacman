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
short const NUMBER_OF_TILE_TYPES = 14;
short const NUMBER_OF_TILES = 418;
short const TILE_WIDTH = 24;
short const TILE_HEIGHT = 24;
short const MAP_WIDTH = 456;
short const MAP_INIT_X_POSITION = (WINDOW_WIDTH - MAP_WIDTH) / 2;
short const MAP_INIT_Y_POSITION = (WINDOW_HEIGHT - TILE_HEIGHT * 22) / 2;

SDL_Rect tilesClips[NUMBER_OF_TILE_TYPES];

enum TileType
{
	LEFT_TILE = 0,
	UP_TILE = 1,
	RIGHT_TILE = 2,
	DOWN_TILE = 3,   
	VERTICAL_PIPE_TILE = 4,
	HORIZONTAL_PIPE_TILE = 5,
	TOP_TILE = 6,
	BOT_TILE = 7,
	TOP_LEFT_TILE = 8,
	TOP_RIGHT_TILE = 9,
	BOT_LEFT_TILE = 10,
	BOT_RIGHT_TILE = 11,
	RIGHT_BORDER_TILE = 12,
	LEFT_BORDER_TILE = 13
};

int main(int argc, char ** argv)
{
	SDL_Window *window = init("MyPacman", WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Renderer *renderer = initRenderer(window);

	SDL_Event ev;
	int delay = 1000 / 60;
	bool hasQuit = false;

	GameTileTexture *tiles[NUMBER_OF_TILES];

	int numberOfLoadedTiles = loadTiles("level.map", tiles, NUMBER_OF_TILES);
	loadTileClips(tilesClips);

	GameTexture *tilesTexture = new GameTexture();
	tilesTexture->loadFromFile("tiles.png", renderer);

	while (!hasQuit) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				hasQuit = true;
			}
		}

		SDL_Delay(delay);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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
	int x = MAP_INIT_X_POSITION;
	int y = MAP_INIT_Y_POSITION;

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

			if (x >= MAP_WIDTH + MAP_INIT_X_POSITION) {
				x = MAP_INIT_X_POSITION;

				y += TILE_HEIGHT;
			}
		}
	}

	map.close();

	return indexOfTile;
}

void loadTileClips(SDL_Rect tilesClips[])
{
	tilesClips[LEFT_TILE].x = 0;
	tilesClips[LEFT_TILE].y = 0;
	tilesClips[LEFT_TILE].w = TILE_WIDTH;
	tilesClips[LEFT_TILE].h = TILE_HEIGHT;

	tilesClips[UP_TILE].x = 24;
	tilesClips[UP_TILE].y = 0;
	tilesClips[UP_TILE].w = TILE_WIDTH;
	tilesClips[UP_TILE].h = TILE_HEIGHT;

	tilesClips[RIGHT_TILE].x = 48;
	tilesClips[RIGHT_TILE].y = 0;
	tilesClips[RIGHT_TILE].w = TILE_WIDTH;
	tilesClips[RIGHT_TILE].h = TILE_HEIGHT;

	tilesClips[DOWN_TILE].x = 72;
	tilesClips[DOWN_TILE].y = 0;
	tilesClips[DOWN_TILE].w = TILE_WIDTH;
	tilesClips[DOWN_TILE].h = TILE_HEIGHT;

	tilesClips[VERTICAL_PIPE_TILE].x = 96;
	tilesClips[VERTICAL_PIPE_TILE].y = 0;
	tilesClips[VERTICAL_PIPE_TILE].w = TILE_WIDTH;
	tilesClips[VERTICAL_PIPE_TILE].h = TILE_HEIGHT;

	tilesClips[HORIZONTAL_PIPE_TILE].x = 120;
	tilesClips[HORIZONTAL_PIPE_TILE].y = 0;
	tilesClips[HORIZONTAL_PIPE_TILE].w = TILE_WIDTH;
	tilesClips[HORIZONTAL_PIPE_TILE].h = TILE_HEIGHT;

	tilesClips[TOP_TILE].x = 120;
	tilesClips[TOP_TILE].y = 0;
	tilesClips[TOP_TILE].w = TILE_WIDTH;
	tilesClips[TOP_TILE].h = TILE_HEIGHT - 2;

	tilesClips[BOT_TILE].x = 96;
	tilesClips[BOT_TILE].y = 24;
	tilesClips[BOT_TILE].w = TILE_WIDTH;
	tilesClips[BOT_TILE].h = TILE_HEIGHT;

	tilesClips[TOP_LEFT_TILE].x = 0;
	tilesClips[TOP_LEFT_TILE].y = 24;
	tilesClips[TOP_LEFT_TILE].w = TILE_WIDTH;
	tilesClips[TOP_LEFT_TILE].h = TILE_HEIGHT;

	tilesClips[TOP_RIGHT_TILE].x = 24;
	tilesClips[TOP_RIGHT_TILE].y = 24;
	tilesClips[TOP_RIGHT_TILE].w = TILE_WIDTH;
	tilesClips[TOP_RIGHT_TILE].h = TILE_HEIGHT;

	tilesClips[BOT_LEFT_TILE].x = 48;
	tilesClips[BOT_LEFT_TILE].y = 24;
	tilesClips[BOT_LEFT_TILE].w = TILE_WIDTH;
	tilesClips[BOT_LEFT_TILE].h = TILE_HEIGHT;

	tilesClips[BOT_RIGHT_TILE].x = 72;
	tilesClips[BOT_RIGHT_TILE].y = 24;
	tilesClips[BOT_RIGHT_TILE].w = TILE_WIDTH;
	tilesClips[BOT_RIGHT_TILE].h = TILE_HEIGHT;

	tilesClips[RIGHT_BORDER_TILE].x = 120;
	tilesClips[RIGHT_BORDER_TILE].y = 24;
	tilesClips[RIGHT_BORDER_TILE].w = TILE_WIDTH;
	tilesClips[RIGHT_BORDER_TILE].h = TILE_HEIGHT;

	tilesClips[LEFT_BORDER_TILE].x = 96;
	tilesClips[LEFT_BORDER_TILE].y = 0;
	tilesClips[LEFT_BORDER_TILE].w = TILE_WIDTH - 2;
	tilesClips[LEFT_BORDER_TILE].h = TILE_HEIGHT;
}