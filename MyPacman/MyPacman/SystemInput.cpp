#include "SystemInput.h"

SystemInput::SystemInput()
{
}


SystemInput::~SystemInput()
{
}

void SystemInput::registerInput()
{
	this->clearInput();

	while (SDL_PollEvent(&this->event) != 0) {
		if (this->event.type == SDL_QUIT) {
			this->commands.push_back(QUIT);
		}
		else if (this->event.type == SDL_KEYDOWN && this->event.key.repeat == 0) {
			switch (this->event.key.keysym.sym) {
			case SDLK_RIGHT:
				this->commands.push_back(DIR_RIGHT);
				break;
			case SDLK_LEFT:
				this->commands.push_back(DIR_LEFT);
				break;
			case SDLK_UP:
				this->commands.push_back(DIR_UP);
				break;
			case SDLK_DOWN:
				this->commands.push_back(DIR_DOWN);
				break;
			default:
				break;
			}
		}
	}
}

void SystemInput::clearInput()
{
	while (this->commands.size() > 0) {
		this->commands.pop_front();
	}
}