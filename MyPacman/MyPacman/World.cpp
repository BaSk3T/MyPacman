#include "World.h"

World::World()
{
}

World::~World()
{
	for each (GameObject *object in this->objects) {
		delete object;
	}
}

void World::run(System &system, SystemGraphics &systemGraphics, SystemInput &systemInput, SystemFont &systemFont)
{
	bool hasQuit = false;

	system.createWindow("MyPacman", World::WINDOW_WIDTH, World::WINDOW_HEIGHT);
	//system.setWindowFullScreen(system.getWindow("MyPacman"));
	systemGraphics.initRenderer(system.getWindow("MyPacman"));

	systemFont.loadFont("arial14", "Fonts/arial.ttf", 14);

	Level level = Level();
	level.loadLevel("Levels/level.map", this->objects, World::WINDOW_WIDTH, World::WINDOW_HEIGHT);
	systemGraphics.createSprite("tile", "Sprites/Common/tiles.png");
	systemGraphics.createSprite("food", "Sprites/Common/food-sprite.png");
	systemGraphics.createSprite("pacman", "Sprites/Pacman/pacman-sprite.png");
	systemGraphics.createSprite("pinky", "Sprites/Ghosts/pinky-sprite.png");
	systemGraphics.createSprite("blinky", "Sprites/Ghosts/blinky-sprite.png");
	systemGraphics.createSprite("inky", "Sprites/Ghosts/inky-sprite.png");
	systemGraphics.createSprite("clyde", "Sprites/Ghosts/clyde-sprite.png");

	this->objects.push_back(new GameObject(2, 20, 20, new PacmanInputComponent(), new PacmanPhysicsComponent(), new PacmanGraphicsComponent()));
	this->objects.push_back(new GameObject(3, WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 - 72, new GhostInputComponent(), new GhostPhysicsComponent(), new GhostGraphicsComponent("pinky")));
	this->objects.push_back(new GameObject(3, WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 - 72, new GhostInputComponent(), new GhostPhysicsComponent(), new GhostGraphicsComponent("blinky")));
	this->objects.push_back(new GameObject(3, WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 - 24, new GhostInputComponent(), new GhostPhysicsComponent(), new GhostGraphicsComponent("inky")));
	this->objects.push_back(new GameObject(3, WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 - 24, new GhostInputComponent(), new GhostPhysicsComponent(), new GhostGraphicsComponent("clyde")));

	this->trail.push_front(CollisionBox(20, 20, 24, 24));

	Timer fpsTimer = Timer();
	Timer capTimer = Timer();
	std::stringstream timeText;

	int countedFrames = 0;
	int avgFPS;
	fpsTimer.start();
	systemGraphics.createTextSprite("fpsTimer");

	while (!hasQuit)
	{
		capTimer.start();
		systemInput.registerInput();

		for each (Command command in  systemInput.commands) {
			if (command == QUIT) {
				hasQuit = true;
			}
		}

		systemGraphics.setDrawColor(0, 0, 0, 0);
		systemGraphics.clear();

		for each (GameObject *object in this->objects) {
			object->update(*this, systemGraphics, systemInput);
		}

		if (this->trail.size() >= 5) {
			this->trail.pop_back();
		}

		avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);

		if (avgFPS > 2000000) {
			avgFPS = 0;
		}

		timeText.str("");
		timeText << "FPS: " << avgFPS;

		systemGraphics.updateTextSprite("fpsTimer", timeText.str().c_str(), systemFont.getFont("arial14"));
		systemGraphics.draw("fpsTimer", WINDOW_WIDTH - WINDOW_WIDTH / 10, WINDOW_HEIGHT - WINDOW_HEIGHT / 10);

		systemGraphics.present();

		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME) {
			//Wait remaining time
			system.delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	system.closeWindow("MyPacman");
}

void World::resolveCollision(GameObject &sender)
{
	for each (GameObject *object in this->objects) {

		if (!this->isInRangeOf(sender.physics->getCollisionBox(), object->physics->getCollisionBox(), World::COLLISION_RANGE)) {
			continue;
		}

		if (this->checkCollision(sender.physics->getCollisionBox(), object->physics->getCollisionBox())) {
			object->send(COLLISION, sender);
			sender.send(COLLISION, *object);
		}
	}
}

bool World::collisionBoxIsColidingWith(int objectId, CollisionBox const &collisionBox)
{
	for each (GameObject *object in this->objects) {
		if (object->objectId != objectId) {
			continue;
		}

		if (!this->isInRangeOf(collisionBox, object->physics->getCollisionBox(), World::COLLISION_RANGE)) {
			continue;
		}

		if (this->checkCollision(collisionBox, object->physics->getCollisionBox())) {
			return true;
		}
	}

	return false;
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