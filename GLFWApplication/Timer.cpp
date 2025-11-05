#if Timer_cpp == 0
#define Timer_cpp


#include "Entry.h"
#include "Timer.h"


FTimer* newTimer(float startingTime, float targetTime, ETimerType type, ETimerActionOnCompletion actionOnComplete)
{
	FTimer* newTimer = new FTimer();
	newTimer->startingTime = startingTime;
	newTimer->TargetTime = targetTime;
	newTimer->currentTime = startingTime;
	newTimer->type = type;
	newTimer->state = ETimerState::Ticking;
	newTimer->actionOnComplete = actionOnComplete;

	if (Engine::FEngine* Engine = GetEngine()) {
		Engine->activeTimers.insert(Engine->activeTimers.end(), newTimer);
	}

	return newTimer;
}

void HandleTimers(float dt)
{	
	if (Engine::FEngine* Engine = GetEngine())
	{
		std::vector<FTimer*> tickedTimers;

		for (FTimer* timer : Engine->activeTimers) {
			if (timer->state == ETimerState::Paused) continue;

			switch (timer->type) {
			case ETimerType::TickUp:

				timer->currentTime += dt;

				if (timer->currentTime >= timer->TargetTime)
					tickedTimers.insert(tickedTimers.end(), timer);

				break;

			case ETimerType::TickDown:

				timer->currentTime -= dt;

				if (timer->currentTime <= timer->TargetTime)
					tickedTimers.insert(tickedTimers.end(), timer);

				break;
			}

			timer->normalizedTime =
				timer->currentTime - timer->startingTime / timer->TargetTime - timer->startingTime;
			//Engine::print(std::to_string(timer->normalizedTime));
		}

		for (FTimer* timer : tickedTimers) {

			switch (timer->actionOnComplete) {
			case ETimerActionOnCompletion::Destroy:

				if (timer->onTickFunc)
					timer->onTickFunc();

				delete timer;

				break;

			case ETimerActionOnCompletion::Repeat:

				if (timer->onTickFunc)
					timer->onTickFunc();

				timer->currentTime = timer->startingTime;

				break;
			}
		}

		tickedTimers.clear();
	}
}


#endif