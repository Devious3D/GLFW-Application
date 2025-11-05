#pragma once
#if Timer_h == 0
#define Timer_h 1


enum class ETimerState {
	None,
	Paused,
	Ticking,
};


enum class ETimerType {
	TickUp,
	TickDown,
};

enum class ETimerActionOnCompletion {
	Destroy,
	Repeat
};

struct FTimer {
	ETimerState state;
	ETimerType type;
	ETimerActionOnCompletion actionOnComplete;

	float currentTime;
	float startingTime;
	float TargetTime;
	float normalizedTime;

	void(*onTickFunc)();
};

FTimer* newTimer(
	 float startingTime,
	 float targetTime,

	ETimerType type,
	ETimerActionOnCompletion actionOnComplete
);

void HandleTimers(float dt);

#endif