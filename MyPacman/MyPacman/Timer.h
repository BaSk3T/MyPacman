#include "SDL.h"

#pragma once
class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 startTicks;
	Uint32 pausedTicks;
	bool paused;
	bool started;
};

