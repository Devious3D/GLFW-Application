#pragma once
#ifndef ListenerEvent_h
#define ListenerEvent_h 1

template <typename T>
class CMemoryHandler;

enum class EListenerAfterUse {
	None,
	Destroy,
};

struct FListener {
	EListenerAfterUse afterUse;
	void(*func)();
	double time = 0.0f;
};

struct FListenerEventComponent {

private:
	CMemoryHandler<FListener> listeners;

public:


	unsigned int listenerLimit = 0;
	FListenerEventComponent(unsigned int listenerLimit);
	void attachListener(EListenerAfterUse afterUse = EListenerAfterUse::None, void(*listenerFunction)());
	void callListeners();
};



#endif