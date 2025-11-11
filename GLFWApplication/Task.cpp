#ifndef Task_cpp 
#define Task_cpp

#include <vector>

#include "EngineDefinitions.h"
#include "Entry.h"

#include "Task.h"

std::vector<FLoggedTask*> delayedFunctions;

void NewTask(uint type, const void(*function))
{
	if (function == nullptr) Engine::ThrowError(std::string("Must include a function"));


	FLoggedTask* newTask = new FLoggedTask;	
	newTask->type = type;
	newTask->function = function;
}


#endif // !Task_cpp 
