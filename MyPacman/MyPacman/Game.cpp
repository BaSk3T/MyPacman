#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include "GameTile.h"
#include "Character.h"
#include "Food.h"
#include "TileType.h"
#include "Direction.h"

SDL_Window *init(char *title, int width, int height);
SDL_Renderer *initRenderer(SDL_Window *window);
void loadMap(char *mapPath, std::vector<GameTile> &tiles, std::vector<Food> &food);
void loadTileClips(SDL_Rect tilesClips[]);
void loadCharacterClips(SDL_Rect characterClips[]);
bool checkCollision(CollisionBox a, CollisionBox b);
bool checkForCollisionWithTile(std::vector<GameTile> &tiles, Character *character, int xOffset, int yOffset);
bool changeCharacterDirectionIfPossible(Direction requestedDirection, Character *character, std::vector<GameTile> &tiles, bool fixAngle);
void moveCharacter(Character *character, const double velocity);
bool isInRangeOf(const CollisionBox a, const CollisionBox b, unsigned int range);

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
double const CHARACTER_VELOCITY = 2;
short const CHARACTER_FRAME_DELAY = 5;
short const CHARACTER_INIT_X_POSITION = MAP_INIT_X_POSITION + (MAP_WIDTH - CHARACTER_WIDTH) / 2;
short const CHARACTER_INIT_Y_POSITION = MAP_INIT_Y_POSITION + (MAP_HEIGHT - CHARACTER_HEIGHT) / 2 + 36;
double const GHOST_VELOCITY = 2;
short const FOOD_WIDTH = 6;
short const FOOD_HEIGHT = 6;

SDL_Rect tilesClips[NUMBER_OF_TILE_TYPES];
SDL_Rect characterClips[NUMBER_OF_CHARACTER_SPRITES];

int main(int argc, char ** argv)
{
	srand(time(NULL));

	SDL_Window *window = init("MyPacman", WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Renderer *renderer = initRenderer(window);

	SDL_Event ev;
	int delay = 1000 / 60;
	bool hasQuit = false;

	std::vector<GameTile> tiles;
	std::vector<Food> food;
	std::deque<CollisionBox> trail;
	trail.push_front(CollisionBox(CHARACTER_INIT_X_POSITION, CHARACTER_INIT_Y_POSITION, CHARACTER_HEIGHT, CHARACTER_WIDTH));

	SDL_Rect pinkyClips[4][2] = {
		{ { 0, 0, 24, 24 },{ 0, 24, 24, 24 } },
		{ { 24, 0, 24, 24 },{ 24, 24, 24, 24 } },
		{ { 48, 0, 24, 24 },{ 48, 24, 24, 24 } },
		{ { 72, 0, 24, 24 },{ 72, 24, 24, 24 } }
	};

	loadMap("level.map", tiles, food);
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

	Character *pinky = new Character(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 72, 2, CHARACTER_FRAME_DELAY, CHARACTER_WIDTH, CHARACTER_HEIGHT);

	GameTexture *pinkyTexture = new GameTexture();
	pinkyTexture->loadFromFile("pinky-sprite.png", renderer);

	GameTexture *characterTexture = new GameTexture();
	characterTexture->loadFromFile("pacman-sprite.png", renderer);

	GameTexture *foodTexture = new GameTexture();
	foodTexture->loadFromFile("food-sprite.png", renderer);

	Direction requestedDirection = RIGHT;
	Direction pinkyRequestedDirection = DOWN;
	Direction pinkyDirection = DOWN;

	int shouldSwitchDirection;
	bool foundTrail = false;

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

		// character 
		changeCharacterDirectionIfPossible(requestedDirection, character, tiles, true);
		moveCharacter(character, CHARACTER_VELOCITY);

		// when pacman doesn't collide with last added trail add new trail
		if (!checkCollision(character->getCollisionBox(), trail.front())) {
			trail.push_front(character->getCollisionBox());
		}

		// remove oldest trail
		if (trail.size() >= 5) {
			trail.pop_back();
		}

		foundTrail = false;

		// starting from 1 because if pinky is colliding with last 1 there will be collision with pacman ( thus pacman is dead )
		for (Uint16 i = 1; i < trail.size(); i++) {

			if (checkCollision(pinky->getCollisionBox(), trail[i])) {
				if (trail[i - 1].x > trail[i].x) {
					pinkyRequestedDirection = RIGHT;
				}
				else if (trail[i - 1].x < trail[i].x) {
					pinkyRequestedDirection = LEFT;
				}
				else if (trail[i - 1].y < trail[i].y) {
					pinkyRequestedDirection = UP;
				}
				else {
					pinkyRequestedDirection = DOWN;
				}

				foundTrail = true;
				break;
			}
		}

		if (!foundTrail) {
			shouldSwitchDirection = (std::rand() % 1000) % 237;

			if (shouldSwitchDirection == 0) {
				if (pinkyRequestedDirection % 2 == 0) {
					pinkyRequestedDirection = (std::rand() % 2) == 1 ? UP : DOWN;
				}
				else {
					pinkyRequestedDirection = (std::rand() % 2) == 1 ? LEFT : RIGHT;
				}
			}
		}

		//pinky
		bool pinkyHasChangedDirection = changeCharacterDirectionIfPossible(pinkyRequestedDirection, pinky, tiles, false);
		moveCharacter(pinky, GHOST_VELOCITY);

		if (pinkyHasChangedDirection) {
			pinkyDirection = pinkyRequestedDirection;
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

		// update displaying of tiles
		for (unsigned int i = 0; i < tiles.size(); i++) {
			tilesTexture->render((int)tiles[i].getX(), (int)tiles[i].getY(), renderer, &tilesClips[tiles[i].getType()]);

			// check if tile is in range of pacman
			if (isInRangeOf(character->getCollisionBox(), tiles[i].getCollisionBox(), 50)) {
				// check if character has colided with tile
				if (checkCollision(character->getCollisionBox(), tiles[i].getCollisionBox())) {
					moveCharacter(character, -CHARACTER_VELOCITY);
				}
			}

			// check if tile is in range of pinky
			if (isInRangeOf(pinky->getCollisionBox(), tiles[i].getCollisionBox(), 50)) {
				// check if pinky has colided with tile
				if (checkCollision(pinky->getCollisionBox(), tiles[i].getCollisionBox())) {
					moveCharacter(pinky, -CHARACTER_VELOCITY);

					// if pinky has switched direction no need to check if it is colliding
					if (pinkyHasChangedDirection) {
						continue;
					}

					if (pinkyRequestedDirection % 2 == 0) {
						pinkyRequestedDirection = (std::rand() % 2) == 1 ? UP : DOWN;
					}
					else {
						pinkyRequestedDirection = (std::rand() % 2) == 1 ? LEFT : RIGHT;
					}
				}
			}
		}

		// update frame of pinky
		pinkyTexture->render((int)pinky->getX(), (int)pinky->getY(), renderer, &pinkyClips[pinkyDirection][pinky->getFrame() / CHARACTER_FRAME_DELAY], pinky->getAngle());
		pinky->increaseFrame();

		// update frame of character
		characterTexture->render((int)character->getX(), (int)character->getY(), renderer, &characterClips[character->getFrame() / CHARACTER_FRAME_DELAY], character->getAngle());
		character->increaseFrame();

		SDL_RenderPresent(renderer);
	}

	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete tilesTexture;
	delete characterTexture;
	delete pinkyTexture;
	delete foodTexture;
	delete character;
	delete pinky;

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

void loadMap(char *mapPath, std::vector<GameTile> &tiles, std::vector<Food> &food)
{
	int x = MAP_INIT_X_POSITION;
	int y = MAP_INIT_Y_POSITION;

	std::ifstream map(mapPath);

	if (!map.is_open()) {
		std::cout << "Unable to load map file!" << std::endl;
	}
	else {
		for (short i = 0; i < NUMBER_OF_TILES; i++) {
			int tyleType = -1;

			map >> tyleType;

			if (map.fail()) {
				std::cout << "Error loading map: Unexpected end of file!" << std::endl;
			}

			if (tyleType > NUMBER_OF_TILE_TYPES) {
				std::cout << "Error loading map: Unrecognized tyle type!" << std::endl;
			}
			else if (1 <= tyleType && tyleType < NUMBER_OF_TILE_TYPES) {
				tiles.push_back(GameTile(x, y, TILE_WIDTH, TILE_HEIGHT, tyleType - 1));
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
}

bool checkCollision(CollisionBox a, CollisionBox b)
{
	//The sides of the rectangles
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.width;
	topA = a.y;
	bottomA = a.y + a.height;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.width;
	topB = b.y;
	bottomB = b.y + b.height;

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

bool checkForCollisionWithTile(std::vector<GameTile> &tiles, Character *character, int xOffset, int yOffset)
{
	CollisionBox offsetRect = character->getCollisionBox();
	offsetRect.x += xOffset;
	offsetRect.y += yOffset;

	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (checkCollision(offsetRect, tiles[i].getCollisionBox())) {
			return true;
		}
	}

	return false;
}

void moveCharacter(Character *character, const double velocity)
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

bool changeCharacterDirectionIfPossible(Direction requestedDirection, Character *character, std::vector<GameTile> &tiles, bool fixAngle)
{
	bool changedDirection = false;

	CollisionBox characterCollisionBox = character->getCollisionBox();

	if (requestedDirection == DOWN) {
		if (!checkForCollisionWithTile(tiles, character, 0, characterCollisionBox.height)) {
			character->setGoingUp(false);
			character->setMovingHorizontal(false);
			changedDirection = true;

			if (fixAngle) {
				character->fixAngle();
			}
		}
	}
	else if (requestedDirection == UP) {
		if (!checkForCollisionWithTile(tiles, character, 0, -characterCollisionBox.height)) {
			character->setGoingUp(true);
			character->setMovingHorizontal(false);
			changedDirection = true;

			if (fixAngle) {
				character->fixAngle();
			}
		}
	}
	else if (requestedDirection == LEFT) {
		if (!checkForCollisionWithTile(tiles, character, -characterCollisionBox.width, 0)) {
			character->setGoingRight(false);
			character->setMovingHorizontal(true);
			changedDirection = true;

			if (fixAngle) {
				character->fixAngle();
			}
		}
	}
	else if (requestedDirection == RIGHT) {
		if (!checkForCollisionWithTile(tiles, character, characterCollisionBox.width, 0)) {
			character->setGoingRight(true);
			character->setMovingHorizontal(true);
			changedDirection = true;

			if (fixAngle) {
				character->fixAngle();
			}
		}
	}

	return changedDirection;
}

bool isInRangeOf(const CollisionBox a, const CollisionBox b, unsigned int range)
{
	int differenceInX = (int)std::abs(a.x - b.x);
	int differenceInY = (int)std::abs(a.y - b.y);

	bool isInRange = false;

	if (differenceInX <= range && differenceInY <= range) {
		isInRange = true;
	}

	return isInRange;
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