#include "Timer.h"
#include "Base.h"

Timer::Timer() {
	startTime = 0;
	pauseTime = 0;

	isPaused = false;
	isStarted = false;
}

Timer::~Timer() {

}

void Timer::start() {
	isStarted = true;
	isPaused = false;
	startTime = SDL_GetTicks();
}

void Timer::stop() {
	isPaused = false;
	isStarted = false;
}

void Timer::paused() {
	if (isStarted == true && isPaused == false) {
		isPaused = true;
		pauseTime = SDL_GetTicks() - startTime;
	}
}

void Timer::unpaused() {
	if (isPaused == true) {
		isPaused = false;
		startTime = SDL_GetTicks() - pauseTime;
		pauseTime = 0;
	}
}

int Timer::getTicks() {
	if (isStarted == true) {
		if (isPaused == true) {
			return pauseTime;
		}
		else {
			return SDL_GetTicks() - startTime;
		}
	}
	return 0;
}

bool Timer::is_started() {
	return isStarted;
}

bool Timer::is_paused() {
	return isPaused;
}