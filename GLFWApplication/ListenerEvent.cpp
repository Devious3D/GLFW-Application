#ifndef ListenerEvent_cpp
#define ListenereEvent_cpp 1

#include "ListenerEvent.h"
#include  "Memory.h"
#include "../Entry.h"

FListenerEventComponent::FListenerEventComponent(unsigned int listnerLimit) {
	this->listenerLimit = listenerLimit;
	this->listeners.Construct(sizeof(FListener) * listnerLimit, listnerLimit, 0);
}

void FListenerEventComponent::attachListener(EListenerAfterUse afterUse = EListenerAfterUse::None, void(*listenerFunction)())
{
	FListener newListener;
	newListener.func = listenerFunction;
	newListener.afterUse = afterUse;
	newListener.time = 1.0f;

	this->listeners.Insert(newListener);
}

void FListenerEventComponent::callListeners()
{
}

#endif