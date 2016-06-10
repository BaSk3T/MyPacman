#include "Level.h"

Rectangle Level::tileClips[] = { { 0, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 24, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 48, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT },
{ 72, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 96, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 120, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 120, 0, Level::TILE_WIDTH, Level::TILE_HEIGHT - 2 },
{ 96, 24, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 0, 24, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 24, 24, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 48, 24, Level::TILE_WIDTH, Level::TILE_HEIGHT },
{ 72, 24, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 120, 24, Level::TILE_WIDTH, Level::TILE_HEIGHT },{ 96, 0, Level::TILE_WIDTH - 2, Level::TILE_HEIGHT } };

Level::Level()
{
}

Level::~Level()
{
}

void Level::loadLevel(char *path, std::vector<GameObject*> &objects, int windowWidth, int windowHeight)
{
	int mapInitPoisitionX = (windowWidth - Level::MAP_WIDTH) / 2;
	int mapInitPositionY = (windowHeight - Level::MAP_HEIGHT) / 2;

	int x = mapInitPoisitionX;
	int y = mapInitPositionY;

	std::ifstream map(path);

	if (!map.is_open()) {
		std::cout << "Unable to load map file!" << std::endl;
	}
	else {
		for (short i = 0; i < Level::NUMBER_OF_TILES; i++) {
			int tyleType = -1;

			map >> tyleType;

			if (map.fail()) {
				std::cout << "Error loading map: Unexpected end of file!" << std::endl;
			}

			if (tyleType > Level::NUMBER_OF_TILE_TYPES) {
				std::cout << "Error loading map: Unrecognized tyle type!" << std::endl;
			}
			else if (1 <= tyleType && tyleType < Level::NUMBER_OF_TILE_TYPES) {
				objects.push_back(new GameObject(x, y, new TileInputComponent(), new TilePhysicsComponent(CollisionBox(x, y, Level::TILE_WIDTH, Level::TILE_HEIGHT)), new TileGraphicsComponent(this->tileClips[tyleType - 1])));
			}
			else if (tyleType - 1 == FOOD) {
				objects.push_back(new GameObject(x, y, new FoodInputComponent(), new FoodPhysicsComponent(CollisionBox(x + (TILE_WIDTH - FOOD_WIDTH) / 2, y + (TILE_HEIGHT - FOOD_HEIGHT) / 2, FOOD_WIDTH, FOOD_HEIGHT)), new FoodGraphicsComponent()));
			}

			x += Level::TILE_WIDTH;

			if (x >= Level::MAP_WIDTH + mapInitPoisitionX) {
				x = mapInitPoisitionX;

				y += Level::TILE_HEIGHT;
			}
		}
	}

	map.close();
}