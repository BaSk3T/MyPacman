#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "GameTile.h"
#include "Character.h"
#include "Food.h"
#include "TileType.h"
#include "Direction.h"
#include "System.h"
#include "SystemGraphics.h"

void loadMap(char *mapPath, std::vector<GameTile> &tiles, std::vector<Food> &food);
void loadTileClips(Rectangle tilesClips[]);
void loadCharacterClips(Rectangle characterClips[]);
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

Rectangle tilesClips[NUMBER_OF_TILE_TYPES];
Rectangle characterClips[NUMBER_OF_CHARACTER_SPRITES];

int main(int argc, char ** argv)
{
	srand(time(NULL));

	System *system = new System();
	SDL_Window *window = system->createWindow("MyPacman", WINDOW_WIDTH, WINDOW_HEIGHT);
	
	SystemGraphics *systemGraphics = new SystemGraphics();
	systemGraphics->initRenderer(window);

	SDL_Event ev;
	int delay = 1000 / 60;
	bool hasQuit = false;

	std::vector<GameTile> tiles;
	std::vector<Food> food;
	std::deque<CollisionBox> trail;
	trail.push_front(CollisionBox(CHARACTER_INIT_X_POSITION, CHARACTER_INIT_Y_POSITION, CHARACTER_HEIGHT, CHARACTER_WIDTH));

	Rectangle pinkyClips[4][2] = {
		{ { 0, 0, 24, 24 },{ 0, 24, 24, 24 } },
		{ { 24, 0, 24, 24 },{ 24, 24, 24, 24 } },
		{ { 48, 0, 24, 24 },{ 48, 24, 24, 24 } },
		{ { 72, 0, 24, 24 },{ 72, 24, 24, 24 } }
	};

	loadMap("Levels/level.map", tiles, food);
	loadTileClips(tilesClips);

	systemGraphics->createSprite("tiles", "Sprites/Common/tiles.png");

	loadCharacterClips(characterClips);

	Character *pacman = new Character(
		CHARACTER_INIT_X_POSITION,
		CHARACTER_INIT_Y_POSITION,
		NUMBER_OF_CHARACTER_SPRITES,
		CHARACTER_FRAME_DELAY,
		CHARACTER_WIDTH,
		CHARACTER_HEIGHT);

	Character *pinky = new Character(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 72, 2, CHARACTER_FRAME_DELAY, CHARACTER_WIDTH, CHARACTER_HEIGHT);

	systemGraphics->createSprite("pinky", "Sprites/Ghosts/pinky-sprite.png");
	systemGraphics->createSprite("pacman", "Sprites/Pacman/pacman-sprite.png");
	systemGraphics->createSprite("food", "Sprites/Common/food-sprite.png");

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

		systemGraphics->setDrawColor(0, 0, 0, 0);
		systemGraphics->clear();

		// pacman 
		changeCharacterDirectionIfPossible(requestedDirection, pacman, tiles, true);
		moveCharacter(pacman, CHARACTER_VELOCITY);

		// when pacman doesn't collide with last added trail add new trail
		if (!checkCollision(pacman->getCollisionBox(), trail.front())) {
			trail.push_front(pacman->getCollisionBox());
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

			systemGraphics->draw("food", food[i].getX(), food[i].getY());

			if (checkCollision(pacman->getCollisionBox(), food[i].getCollisionBox())) {
				food[i].setIsEaten(true);
			}
		}

		// update displaying of tiles
		for (unsigned int i = 0; i < tiles.size(); i++) {
			systemGraphics->draw("tiles", (int)tiles[i].getX(), (int)tiles[i].getY(), tilesClips[tiles[i].getType()]);

			// check if tile is in range of pacman
			if (isInRangeOf(pacman->getCollisionBox(), tiles[i].getCollisionBox(), 50)) {
				// check if character has colided with tile
				if (checkCollision(pacman->getCollisionBox(), tiles[i].getCollisionBox())) {
					moveCharacter(pacman, -CHARACTER_VELOCITY);
				}
			}

			// if pinky has switched direction no need to check if it is colliding
			if (pinkyHasChangedDirection) {
				continue;
			}
			
			// check if tile is in range of pinky
			if (isInRangeOf(pinky->getCollisionBox(), tiles[i].getCollisionBox(), 50)) {
				// check if pinky has colided with tile
				if (checkCollision(pinky->getCollisionBox(), tiles[i].getCollisionBox())) {
					moveCharacter(pinky, -CHARACTER_VELOCITY);

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
		systemGraphics->draw("pinky", (int)pinky->getX(), (int)pinky->getY(), pinkyClips[pinkyDirection][pinky->getFrame() / CHARACTER_FRAME_DELAY], pinky->getAngle());
		pinky->increaseFrame();

		// update frame of character
		systemGraphics->draw("pacman", (int)pacman->getX(), (int)pacman->getY(), characterClips[pacman->getFrame() / CHARACTER_FRAME_DELAY], pacman->getAngle());
		pacman->increaseFrame();

		systemGraphics->present();
	}

	system->closeWindow(window);

	delete pacman;
	delete pinky;

	delete systemGraphics;
	delete system;

	return 0;
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
		if (!isInRangeOf(offsetRect, tiles[i].getCollisionBox(), 50)) {
			continue;
		}

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
		}
	}
	else if (requestedDirection == UP) {
		if (!checkForCollisionWithTile(tiles, character, 0, -characterCollisionBox.height)) {
			character->setGoingUp(true);
			character->setMovingHorizontal(false);
			changedDirection = true;
		}
	}
	else if (requestedDirection == LEFT) {
		if (!checkForCollisionWithTile(tiles, character, -characterCollisionBox.width, 0)) {
			character->setGoingRight(false);
			character->setMovingHorizontal(true);
			changedDirection = true;
		}
	}
	else if (requestedDirection == RIGHT) {
		if (!checkForCollisionWithTile(tiles, character, characterCollisionBox.width, 0)) {
			character->setGoingRight(true);
			character->setMovingHorizontal(true);
			changedDirection = true;
		}
	}

	if (fixAngle) {
		character->fixAngle();
	}

	return changedDirection;
}

bool isInRangeOf(const CollisionBox a, const CollisionBox b, unsigned int range)
{
	unsigned int differenceInX = (int)std::abs(a.x - b.x);
	unsigned int differenceInY = (int)std::abs(a.y - b.y);

	bool isInRange = false;

	if (differenceInX <= range && differenceInY <= range) {
		isInRange = true;
	}

	return isInRange;
}

void loadTileClips(Rectangle tilesClips[])
{
	tilesClips[LEFT_TILE].x = 0;
	tilesClips[LEFT_TILE].y = 0;
	tilesClips[LEFT_TILE].width = TILE_WIDTH;
	tilesClips[LEFT_TILE].height = TILE_HEIGHT;

	tilesClips[UP_TILE].x = 24;
	tilesClips[UP_TILE].y = 0;
	tilesClips[UP_TILE].width = TILE_WIDTH;
	tilesClips[UP_TILE].height = TILE_HEIGHT;

	tilesClips[RIGHT_TILE].x = 48;
	tilesClips[RIGHT_TILE].y = 0;
	tilesClips[RIGHT_TILE].width = TILE_WIDTH;
	tilesClips[RIGHT_TILE].height = TILE_HEIGHT;

	tilesClips[DOWN_TILE].x = 72;
	tilesClips[DOWN_TILE].y = 0;
	tilesClips[DOWN_TILE].width = TILE_WIDTH;
	tilesClips[DOWN_TILE].height = TILE_HEIGHT;

	tilesClips[VERTICAL_PIPE_TILE].x = 96;
	tilesClips[VERTICAL_PIPE_TILE].y = 0;
	tilesClips[VERTICAL_PIPE_TILE].width = TILE_WIDTH;
	tilesClips[VERTICAL_PIPE_TILE].height = TILE_HEIGHT;

	tilesClips[HORIZONTAL_PIPE_TILE].x = 120;
	tilesClips[HORIZONTAL_PIPE_TILE].y = 0;
	tilesClips[HORIZONTAL_PIPE_TILE].width = TILE_WIDTH;
	tilesClips[HORIZONTAL_PIPE_TILE].height = TILE_HEIGHT;

	tilesClips[TOP_TILE].x = 120;
	tilesClips[TOP_TILE].y = 0;
	tilesClips[TOP_TILE].width = TILE_WIDTH;
	tilesClips[TOP_TILE].height = TILE_HEIGHT - 2;

	tilesClips[BOT_TILE].x = 96;
	tilesClips[BOT_TILE].y = 24;
	tilesClips[BOT_TILE].width = TILE_WIDTH;
	tilesClips[BOT_TILE].height = TILE_HEIGHT;

	tilesClips[TOP_LEFT_TILE].x = 0;
	tilesClips[TOP_LEFT_TILE].y = 24;
	tilesClips[TOP_LEFT_TILE].width = TILE_WIDTH;
	tilesClips[TOP_LEFT_TILE].height = TILE_HEIGHT;

	tilesClips[TOP_RIGHT_TILE].x = 24;
	tilesClips[TOP_RIGHT_TILE].y = 24;
	tilesClips[TOP_RIGHT_TILE].width = TILE_WIDTH;
	tilesClips[TOP_RIGHT_TILE].height = TILE_HEIGHT;

	tilesClips[BOT_LEFT_TILE].x = 48;
	tilesClips[BOT_LEFT_TILE].y = 24;
	tilesClips[BOT_LEFT_TILE].width = TILE_WIDTH;
	tilesClips[BOT_LEFT_TILE].height = TILE_HEIGHT;

	tilesClips[BOT_RIGHT_TILE].x = 72;
	tilesClips[BOT_RIGHT_TILE].y = 24;
	tilesClips[BOT_RIGHT_TILE].width = TILE_WIDTH;
	tilesClips[BOT_RIGHT_TILE].height = TILE_HEIGHT;

	tilesClips[RIGHT_BORDER_TILE].x = 120;
	tilesClips[RIGHT_BORDER_TILE].y = 24;
	tilesClips[RIGHT_BORDER_TILE].width = TILE_WIDTH;
	tilesClips[RIGHT_BORDER_TILE].height = TILE_HEIGHT;

	tilesClips[LEFT_BORDER_TILE].x = 96;
	tilesClips[LEFT_BORDER_TILE].y = 0;
	tilesClips[LEFT_BORDER_TILE].width = TILE_WIDTH - 2;
	tilesClips[LEFT_BORDER_TILE].height = TILE_HEIGHT;
}

void loadCharacterClips(Rectangle characterClips[])
{
	characterClips[0].x = 0;
	characterClips[0].y = 0;
	characterClips[0].width = CHARACTER_WIDTH;
	characterClips[0].height = CHARACTER_HEIGHT;

	characterClips[1].x = 24;
	characterClips[1].y = 0;
	characterClips[1].width = CHARACTER_WIDTH;
	characterClips[1].height = CHARACTER_HEIGHT;

	characterClips[2].x = 48;
	characterClips[2].y = 0;
	characterClips[2].width = CHARACTER_WIDTH;
	characterClips[2].height = CHARACTER_HEIGHT;
}