#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "GameTileTexture.h"
#include "Character.h"
#include "Food.h"

SDL_Window *init(char *title, int width, int height);
SDL_Renderer *initRenderer(SDL_Window *window);
int loadMap(char *mapPath, GameTileTexture *tiles[], int numberOfTiles, std::vector<Food> &food);
void loadTileClips(SDL_Rect tilesClips[]);
void loadCharacterClips(SDL_Rect characterClips[]);
bool checkCollision(SDL_Rect a, SDL_Rect b);
bool checkForCollisionWithTile(GameTileTexture *tiles[], int numberOfLoadedTiles, Character *character, int xOffset, int yOffset);
void moveCharacter(Character *character, const short velocity);

short const WINDOW_HEIGHT = 640;
short const WINDOW_WIDTH = 860;
short const NUMBER_OF_TILE_TYPES = 15;
short const NUMBER_OF_TILES = 418;
short const NUMBER_OF_CHARACTER_SPRITES = 3;
short const TILE_WIDTH = 24;
short const TILE_HEIGHT = 24;
short const MAP_COLS = 19;
short const MAP_ROWS = 22;
short const MAP_WIDTH = MAP_COLS * TILE_WIDTH;
short const MAP_HEIGHT = MAP_ROWS * TILE_HEIGHT;
short const MAP_INIT_X_POSITION = (WINDOW_WIDTH - MAP_WIDTH) / 2;
short const MAP_INIT_Y_POSITION = (WINDOW_HEIGHT - MAP_HEIGHT) / 2;
short const CHARACTER_WIDTH = 24;
short const CHARACTER_HEIGHT = 24;
short const CHARACTER_VELOCITY = 2;
short const CHARACTER_FRAME_DELAY = 5;
short const CHARACTER_INIT_X_POSITION = MAP_INIT_X_POSITION + (MAP_WIDTH - CHARACTER_WIDTH) / 2;
short const CHARACTER_INIT_Y_POSITION = MAP_INIT_Y_POSITION + (MAP_HEIGHT - CHARACTER_HEIGHT) / 2 + 36;
short const FOOD_WIDTH = 6;
short const FOOD_HEIGHT = 6;

SDL_Rect tilesClips[NUMBER_OF_TILE_TYPES];
SDL_Rect characterClips[NUMBER_OF_CHARACTER_SPRITES];

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
	LEFT_BORDER_TILE = 13,
	FOOD = 14
};

enum Direction
{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};

int main(int argc, char ** argv)
{
	SDL_Window *window = init("MyPacman", WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Renderer *renderer = initRenderer(window);

	SDL_Event ev;
	int delay = 1000 / 60;
	bool hasQuit = false;

	GameTileTexture *tiles[NUMBER_OF_TILES];
	std::vector<Food> food;

	int numberOfLoadedTiles = loadMap("level.map", tiles, NUMBER_OF_TILES, food);
	loadTileClips(tilesClips);

	GameTexture *tilesTexture = new GameTexture();
	tilesTexture->loadFromFile("tiles.png", renderer);

	loadCharacterClips(characterClips);

	Character *character = new Character(
		CHARACTER_INIT_X_POSITION,
		CHARACTER_INIT_Y_POSITION,
		NUMBER_OF_CHARACTER_SPRITES,
		CHARACTER_FRAME_DELAY,
		CHARACTER_WIDTH,
		CHARACTER_HEIGHT);

	GameTexture *characterTexture = new GameTexture();
	characterTexture->loadFromFile("pacman-sprites.png", renderer);

	GameTexture *foodTexture = new GameTexture();
	foodTexture->loadFromFile("food-sprite.png", renderer);

	Direction requestedDirection = RIGHT;

	while (!hasQuit) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				hasQuit = true;
			}
			else if (ev.type == SDL_KEYDOWN && ev.key.repeat == 0) {
				switch (ev.key.keysym.sym) {
				case SDLK_RIGHT:
					requestedDirection = RIGHT;
					break;
				case SDLK_LEFT:
					requestedDirection = LEFT;
					break;
				case SDLK_UP:
					requestedDirection = UP;
					break;
				case SDLK_DOWN:
					requestedDirection = DOWN;
					break;
				default:
					break;
				}
			}
		}

		SDL_Delay(delay);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		if (requestedDirection == DOWN) {
			if (!checkForCollisionWithTile(tiles, numberOfLoadedTiles, character, 0, CHARACTER_HEIGHT)) {
				character->setGoingUp(false);
				character->setMovingHorizontal(false);
				character->fixAngle();
			}
		}
		else if (requestedDirection == UP) {
			if (!checkForCollisionWithTile(tiles, numberOfLoadedTiles, character, 0, -CHARACTER_HEIGHT)) {
				character->setGoingUp(true);
				character->setMovingHorizontal(false);
				character->fixAngle();
			}
		}
		else if (requestedDirection == LEFT) {
			if (!checkForCollisionWithTile(tiles, numberOfLoadedTiles, character, -CHARACTER_WIDTH, 0)) {
				character->setGoingRight(false);
				character->setMovingHorizontal(true);
				character->fixAngle();
			}
		}
		else if (requestedDirection == RIGHT) {
			if (!checkForCollisionWithTile(tiles, numberOfLoadedTiles, character, CHARACTER_WIDTH, 0)) {
				character->setGoingRight(true);
				character->setMovingHorizontal(true);
				character->fixAngle();
			}
		}

		// update frame of character
		characterTexture->render(character->getX(), character->getY(), renderer, &characterClips[character->getFrame() / CHARACTER_FRAME_DELAY], character->getAngle());
		character->increaseFrame();
		moveCharacter(character, CHARACTER_VELOCITY);

		// update displaying of tiles
		for (int i = 0; i < numberOfLoadedTiles; i++) {
			tilesTexture->render(tiles[i]->getX(), tiles[i]->getY(), renderer, &tilesClips[tiles[i]->getType()]);

			// check if character has colided with any tile
			if (checkCollision(character->getCollisionBox(), tiles[i]->getCollisionBox())) {
				moveCharacter(character, -CHARACTER_VELOCITY);
			}
		}

		for (unsigned int i = 0; i < food.size(); i++) {
			if (food[i].getIsEaten()) {
				continue;
			}

			foodTexture->render(food[i].getX(), food[i].getY(), renderer);

			if (checkCollision(character->getCollisionBox(), food[i].getCollisionBox())) {
				food[i].setIsEaten(true);
			}
		}

		SDL_RenderPresent(renderer);
	}

	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete tilesTexture;
	delete characterTexture;
	delete foodTexture;
	delete character;

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

int loadMap(char *mapPath, GameTileTexture *tiles[], int numberOfTiles, std::vector<Food> &food)
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

			if (tyleType > NUMBER_OF_TILE_TYPES) {
				std::cout << "Error loading map: Unrecognized tyle type!" << std::endl;
			}
			else if (1 <= tyleType && tyleType < NUMBER_OF_TILE_TYPES) {
				tiles[indexOfTile] = new GameTileTexture(x, y, TILE_WIDTH, TILE_HEIGHT, tyleType - 1);
				indexOfTile++;
			}
			else if (tyleType - 1 == FOOD) {
				food.push_back(Food(x, y, x + (TILE_WIDTH - FOOD_WIDTH) / 2, y + (TILE_HEIGHT - FOOD_HEIGHT) / 2, FOOD_WIDTH, FOOD_HEIGHT));
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

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

bool checkForCollisionWithTile(GameTileTexture *tiles[], int numberOfLoadedTiles, Character *character, int xOffset, int yOffset)
{
	SDL_Rect offsetRect = character->getCollisionBox();
	offsetRect.x += xOffset;
	offsetRect.y += yOffset;

	for (int i = 0; i < numberOfLoadedTiles; i++) {
		if (checkCollision(offsetRect, tiles[i]->getCollisionBox())) {
			return true;
		}
	}

	return false;
}

void moveCharacter(Character *character, const short velocity)
{
	if (character->getMovingHorizontal()) {
		if (character->getGoingRight()) {
			character->setX(character->getX() + velocity);
		}
		else {
			character->setX(character->getX() - velocity);
		}
	}
	else {
		if (character->getGoingUp()) {
			character->setY(character->getY() - velocity);
		}
		else {
			character->setY(character->getY() + velocity);
		}
	}

	character->shifCollisionBox();
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

void loadCharacterClips(SDL_Rect characterClips[])
{
	characterClips[0].x = 0;
	characterClips[0].y = 0;
	characterClips[0].w = CHARACTER_WIDTH;
	characterClips[0].h = CHARACTER_HEIGHT;

	characterClips[1].x = 24;
	characterClips[1].y = 0;
	characterClips[1].w = CHARACTER_WIDTH;
	characterClips[1].h = CHARACTER_HEIGHT;

	characterClips[2].x = 48;
	characterClips[2].y = 0;
	characterClips[2].w = CHARACTER_WIDTH;
	characterClips[2].h = CHARACTER_HEIGHT;
}