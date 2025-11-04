#pragma once
#if Timer_h == 0
#define Timer_h 1


enum class TimerState {
	None,
	Paused,
	Ticking,
};

enum class TimerType {
	TickUp,
	TickDown,
	Repeating,
};

struct Timer {
	signed int currentTime;
	signed int startingTime;
	unsigned int TargetTime;
	unsigned int id;
	signed int normalizedTime;

	TimerState state;
	TimerType type;
};

static void newTimer(unsigned int startingTime, unsigned int targetTime, TimerType type);

#endif