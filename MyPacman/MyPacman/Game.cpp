#include <cstdlib>
#include <ctime>

#include "System.h"
#include "SystemGraphics.h"
#include "SystemInput.h"
#include "World.h"

//bool checkForCollisionWithTile(std::vector<GameTile> &tiles, Character *character, int xOffset, int yOffset);
//bool changeCharacterDirectionIfPossible(Command requestedDirection, Character *character, std::vector<GameTile> &tiles, bool fixAngle);
//void moveCharacter(Character *character, const double velocity);

//double const GHOST_VELOCITY = 2;
//short const FOOD_WIDTH = 6;
//short const FOOD_HEIGHT = 6;

int main(int argc, char ** argv)
{
	srand(time(NULL));

	System *system = new System();
	SystemGraphics *systemGraphics = new SystemGraphics();
	SystemInput *systemInput = new SystemInput();

	World world = World();
	world.run(*system, *systemGraphics, *systemInput);

//	std::deque<CollisionBox> trail;
//	trail.push_front(CollisionBox(CHARACTER_INIT_X_POSITION, CHARACTER_INIT_Y_POSITION, CHARACTER_HEIGHT, CHARACTER_WIDTH));
//
//	Rectangle pinkyClips[4][2] = {
//		{ { 0, 0, 24, 24 },{ 0, 24, 24, 24 } },
//		{ { 24, 0, 24, 24 },{ 24, 24, 24, 24 } },
//		{ { 48, 0, 24, 24 },{ 48, 24, 24, 24 } },
//		{ { 72, 0, 24, 24 },{ 72, 24, 24, 24 } }
//	};
//
//	Character *pinky = new Character(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 72, 2, CHARACTER_FRAME_DELAY, CHARACTER_WIDTH, CHARACTER_HEIGHT);
//
//	systemGraphics->createSprite("pinky", "Sprites/Ghosts/pinky-sprite.png");
//
//	Command requestedDirection = DIR_RIGHT;
//	Command pinkyRequestedDirection = DIR_DOWN;
//	Command pinkyDirection = DIR_DOWN;
//
//	int shouldSwitchDirection;
//	bool foundTrail = false;
//
//	while (!hasQuit) {
//
//		// pacman 
//		changeCharacterDirectionIfPossible(requestedDirection, pacman, tiles, true);
//		moveCharacter(pacman, CHARACTER_VELOCITY);
//
//		// when pacman doesn't collide with last added trail add new trail
//		if (!checkCollision(pacman->getCollisionBox(), trail.front())) {
//			trail.push_front(pacman->getCollisionBox());
//		}
//
//		// remove oldest trail
//		if (trail.size() >= 5) {
//			trail.pop_back();
//		}
//
//		foundTrail = false;
//
//		// starting from 1 because if pinky is colliding with last 1 there will be collision with pacman ( thus pacman is dead )
//		for (Uint16 i = 1; i < trail.size(); i++) {
//
//			if (checkCollision(pinky->getCollisionBox(), trail[i])) {
//				if (trail[i - 1].x > trail[i].x) {
//					pinkyRequestedDirection = DIR_RIGHT;
//				}
//				else if (trail[i - 1].x < trail[i].x) {
//					pinkyRequestedDirection = DIR_LEFT;
//				}
//				else if (trail[i - 1].y < trail[i].y) {
//					pinkyRequestedDirection = DIR_UP;
//				}
//				else {
//					pinkyRequestedDirection = DIR_DOWN;
//				}
//
//				foundTrail = true;
//				break;
//			}
//		}
//
//		if (!foundTrail) {
//			shouldSwitchDirection = (std::rand() % 1000) % 237;
//
//			if (shouldSwitchDirection == 0) {
//				if (pinkyRequestedDirection % 2 == 0) {
//					pinkyRequestedDirection = (std::rand() % 2) == 1 ? DIR_UP : DIR_DOWN;
//				}
//				else {
//					pinkyRequestedDirection = (std::rand() % 2) == 1 ? DIR_LEFT : DIR_RIGHT;
//				}
//			}
//		}
//
//		//pinky
//		bool pinkyHasChangedDirection = changeCharacterDirectionIfPossible(pinkyRequestedDirection, pinky, tiles, false);
//		moveCharacter(pinky, GHOST_VELOCITY);
//
//		if (pinkyHasChangedDirection) {
//			pinkyDirection = pinkyRequestedDirection;
//		}
//
//		for (unsigned int i = 0; i < food.size(); i++) {
//			if (food[i].getIsEaten()) {
//				continue;
//			}
//
//			systemGraphics->draw("food", food[i].getX(), food[i].getY());
//
//			if (checkCollision(pacman->getCollisionBox(), food[i].getCollisionBox())) {
//				food[i].setIsEaten(true);
//			}
//		}
//
//		// update displaying of tiles
//		for (unsigned int i = 0; i < tiles.size(); i++) {
//
//			// check if tile is in range of pacman
//			if (isInRangeOf(pacman->getCollisionBox(), tiles[i].getCollisionBox(), 50)) {
//				// check if character has colided with tile
//				if (checkCollision(pacman->getCollisionBox(), tiles[i].getCollisionBox())) {
//					moveCharacter(pacman, -CHARACTER_VELOCITY);
//				}
//			}
//
//			// if pinky has switched direction no need to check if it is colliding
//			if (pinkyHasChangedDirection) {
//				continue;
//			}
//
//			// check if tile is in range of pinky
//			if (isInRangeOf(pinky->getCollisionBox(), tiles[i].getCollisionBox(), 50)) {
//				// check if pinky has colided with tile
//				if (checkCollision(pinky->getCollisionBox(), tiles[i].getCollisionBox())) {
//					moveCharacter(pinky, -CHARACTER_VELOCITY);
//
//					if (pinkyRequestedDirection % 2 == 0) {
//						pinkyRequestedDirection = (std::rand() % 2) == 1 ? DIR_UP : DIR_DOWN;
//					}
//					else {
//						pinkyRequestedDirection = (std::rand() % 2) == 1 ? DIR_LEFT : DIR_RIGHT;
//					}
//				}
//			}
//		}
//
//		// update frame of pinky
//		systemGraphics->draw("pinky", (int)pinky->getX(), (int)pinky->getY(), pinkyClips[pinkyDirection][pinky->getFrame() / CHARACTER_FRAME_DELAY], pinky->getAngle());
//		pinky->increaseFrame();
//
//	}
//
//	delete pacman;
//	delete pinky;
//
	delete systemGraphics;
	delete systemInput;
	delete system;
//
	return 0;
}
//
//bool checkForCollisionWithTile(std::vector<GameTile> &tiles, Character *character, int xOffset, int yOffset)
//{
//	CollisionBox offsetRect = character->getCollisionBox();
//	offsetRect.x += xOffset;
//	offsetRect.y += yOffset;
//
//	for (unsigned int i = 0; i < tiles.size(); i++) {
//		if (!isInRangeOf(offsetRect, tiles[i].getCollisionBox(), 50)) {
//			continue;
//		}
//
//		if (checkCollision(offsetRect, tiles[i].getCollisionBox())) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//void moveCharacter(Character *character, const double velocity)
//{
//	if (character->getMovingHorizontal()) {
//		if (character->getGoingRight()) {
//			character->setX(character->getX() + velocity);
//		}
//		else {
//			character->setX(character->getX() - velocity);
//		}
//	}
//	else {
//		if (character->getGoingUp()) {
//			character->setY(character->getY() - velocity);
//		}
//		else {
//			character->setY(character->getY() + velocity);
//		}
//	}
//
//	character->shifCollisionBox();
//}
//
//bool changeCharacterDirectionIfPossible(Command requestedDirection, Character *character, std::vector<GameTile> &tiles, bool fixAngle)
//{
//	bool changedDirection = false;
//
//	CollisionBox characterCollisionBox = character->getCollisionBox();
//
//	if (requestedDirection == DIR_DOWN) {
//		if (!checkForCollisionWithTile(tiles, character, 0, characterCollisionBox.height)) {
//			character->setGoingUp(false);
//			character->setMovingHorizontal(false);
//			changedDirection = true;
//		}
//	}
//	else if (requestedDirection == DIR_UP) {
//		if (!checkForCollisionWithTile(tiles, character, 0, -characterCollisionBox.height)) {
//			character->setGoingUp(true);
//			character->setMovingHorizontal(false);
//			changedDirection = true;
//		}
//	}
//	else if (requestedDirection == DIR_LEFT) {
//		if (!checkForCollisionWithTile(tiles, character, -characterCollisionBox.width, 0)) {
//			character->setGoingRight(false);
//			character->setMovingHorizontal(true);
//			changedDirection = true;
//		}
//	}
//	else if (requestedDirection == DIR_RIGHT) {
//		if (!checkForCollisionWithTile(tiles, character, characterCollisionBox.width, 0)) {
//			character->setGoingRight(true);
//			character->setMovingHorizontal(true);
//			changedDirection = true;
//		}
//	}
//
//	if (fixAngle) {
//		character->fixAngle();
//	}
//
//	return changedDirection;
//}