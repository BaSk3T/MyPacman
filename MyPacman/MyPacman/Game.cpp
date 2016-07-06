#include <cstdlib>
#include <ctime>

#include "System.h"
#include "SystemGraphics.h"
#include "SystemInput.h"
#include "SystemFont.h"
#include "World.h"

int main(int argc, char ** argv)
{
	srand(time(NULL));

	System *system = new System();
	SystemGraphics *systemGraphics = new SystemGraphics();
	SystemInput *systemInput = new SystemInput();
	SystemFont *systemFont = new SystemFont();

	World world = World();
	world.run(*system, *systemGraphics, *systemInput, *systemFont);

	delete systemFont;
	delete systemGraphics;
	delete systemInput;
	delete system;

	return 0;
}