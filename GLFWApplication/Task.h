#pragma once
#ifndef Task_h
#define Task_h  1

#define TASK_DELAY 1
#define TASK_AFTER_RENDER 2
#define TASK_BEFORE_RENDER 3 


struct FLoggedTask {
	unsigned int id = 0;
	unsigned int type = 0;
	bool repeatFunction = false;
	const void(*function) = nullptr;
};

void NewTask(uint type = 1, bool repeats = false, const void(*function) = nullptr);
void removeTask(uint id = 0);

void retrivesTasksOfType(uint type = 1);
void handleTaskType(uint type = 1);

#endif // !