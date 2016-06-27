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

	delete systemGraphics;
	delete systemInput;
	delete system;

	return 0;
}