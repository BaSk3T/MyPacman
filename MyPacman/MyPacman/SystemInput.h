#include <deque>
#include <SDL.h>
#include "Command.h"

#pragma once
class SystemInput
{
public:
	std::deque<Command> commands;

	SystemInput();
	~SystemInput();

	void registerInput();

private:
	SDL_Event event;

	void clearInput();
};

