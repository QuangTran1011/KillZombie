#pragma once
#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void paused();
	void unpaused();

	int getTicks();

	bool is_started();
	bool is_paused();

private:
	int startTime;
	int pauseTime;

	bool isPaused;
	bool isStarted;
};


#endif // !TIMER_H
