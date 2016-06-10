#include "World.h"

World::World()
{
}

World::~World()
{
	for (Uint16 i = 0; i < this->objects.size(); i++) {
		delete this->objects[i];
	}
}

void World::run(System &system, SystemGraphics &systemGraphics, SystemInput &systemInput)
{
	bool hasQuit = false;

	system.createWindow("MyPacman", World::WINDOW_WIDTH, World::WINDOW_HEIGHT);
	systemGraphics.initRenderer(system.getWindow("MyPacman"));

	Level level = Level();
	level.loadLevel("Levels/level.map", this->objects, World::WINDOW_WIDTH, World::WINDOW_HEIGHT);
	systemGraphics.createSprite("tile", "Sprites/Common/tiles.png");
	systemGraphics.createSprite("food", "Sprites/Common/food-sprite.png");
	systemGraphics.createSprite("pacman", "Sprites/Pacman/pacman-sprite.png");

	this->objects.push_back(new GameObject(20, 20, new PacmanInputComponent(), new PacmanPhysicsComponent, new PacmanGraphicsComponent()));

	while (!hasQuit)
	{
		systemInput.registerInput();

		for (Uint16 i = 0; i < systemInput.commands.size(); i++) {
			if (systemInput.commands[i] == QUIT) {
				hasQuit = true;
			}
		}

		system.delay(this->delay);
		systemGraphics.setDrawColor(0, 0, 0, 0);
		systemGraphics.clear();

		for (Uint16 i = 0; i < this->objects.size(); i++) {
			this->objects[i]->update(*this, systemGraphics, systemInput);
		}

		systemGraphics.present();
	}

	system.closeWindow("MyPacman");
}

bool World::checkCollision(CollisionBox const &a, CollisionBox const &b)
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

bool World::isInRangeOf(CollisionBox const &a, CollisionBox const &b, unsigned int range)
{
	unsigned int differenceInX = (int)std::abs(a.x - b.x);
	unsigned int differenceInY = (int)std::abs(a.y - b.y);

	bool isInRange = false;

	if (differenceInX <= range && differenceInY <= range) {
		isInRange = true;
	}

	return isInRange;
}