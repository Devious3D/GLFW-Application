#ifndef Task_cpp 
#define Task_cpp 1

#include <vector>

#include "Entry.h" // Engine Definitions

#include "Task.h"

using namespace TaskDefinitions;
 
int NewTask(unsigned int type, bool repeats, void(*function)())
{
	using namespace std;

	if (function == nullptr) ThrowError(std::string("Must include a function"));

	FTaskLog newTask(type, 0, repeats, function);
	

	/*if (Engine::FEngine* Engine = GetEngine()) {
		newTask.id = Engine->loggedTasks.size() + 1;
	}*/

	return newTask.id;
}

bool removeTask(unsigned int id)
{
	bool removed = false;

	if (Engine::FEngine* Engine = GetEngine()) {
		for (int i = 0; i < Engine->loggedTasks.size(); i++) {
			
			FTaskLog currentTask = Engine->loggedTasks[i];
			if (currentTask.id != id) continue;


			break;
;		}
	}

	return removed;
}

void retrivesTasksOfType(unsigned int type)
{


}

void handleTaskType(unsigned int type)
{

}


#endif // !Task_cpp 
