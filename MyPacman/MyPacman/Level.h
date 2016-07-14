#include <vector>
#include <fstream>
#include "TileType.h"
#include "TilePhysicsComponent.h"
#include "TileGraphicsComponent.h"
#include "TileInputComponent.h"
#include "FoodPhysicsComponent.h"
#include "FoodInputComponent.h"
#include "FoodGraphicsComponent.h"

#pragma once
class Level
{
public:
	static const int TILE_WIDTH = 24;
	static const int TILE_HEIGHT = 24;
	static const int MAP_COLS = 19;
	static const int MAP_ROWS = 22;
	static const int MAP_WIDTH = MAP_COLS * TILE_WIDTH;
	static const int MAP_HEIGHT = MAP_ROWS * TILE_HEIGHT;
	static const int NUMBER_OF_TILES = MAP_COLS * MAP_ROWS;
	static const int NUMBER_OF_TILE_TYPES = 15;
	static const int FOOD_WIDTH = 6;
	static const int FOOD_HEIGHT = 6;
	static const int TILE_ID = 0;
	static const int FOOD_ID = 1;

	Level();
	~Level();

	void loadLevel(char *path, std::vector<GameObject*> *objects, int windowWidth, int windowHeight);
private :
	static Rectangle tileClips[];
};

