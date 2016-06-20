#include <cstdlib>
#include <ctime>

#include "System.h"
#include "SystemGraphics.h"
#include "SystemInput.h"
#include "World.h"

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
//	bool foundTrail = false;
//
//	while (!hasQuit) {
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
//		if (pinkyHasChangedDirection) {
//			pinkyDirection = pinkyRequestedDirection;
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
//		}
//	}
//
	delete systemGraphics;
	delete systemInput;
	delete system;

	return 0;
}