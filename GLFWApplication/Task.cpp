#ifndef Task_cpp 
#define Task_cpp 1

#include <vector>

#include "EngineDefinitions.h"
#include "Entry.h"

#include "Task.h"

 
void NewTask(uint type = 1, bool repeats = false, const void(*function) = nullptr)
{
	using namespace std;

	if (function == nullptr) Engine::ThrowError(std::string("Must include a function"));

	FLoggedTask newTask;
	newTask.type = type;
	newTask.repeatFunction = repeats;
	newTask.function = function;

	if (Engine::FEngine* Engine = GetEngine()) {
		if (vector<FLoggedTask>* engine_logged_tasks = (vector<FLoggedTask>*)Engine->loggedTasks) {
			engine_logged_tasks->insert(engine_logged_tasks->end(), newTask);
		}
	}

}

void removeTask(uint id)
{

}

void retrivesTasksOfType(uint type)
{


}

void handleTaskType(uint type)
{

}


#endif // !Task_cpp 
