#pragma once
#ifndef Task_h
#define Task_h  1

#define TASK_DELAY 1
#define TASK_AFTER_RENDER 2
#define TASK_BEFORE_RENDER 3 



int NewTask(unsigned int type = 1, bool repeats = false, const void(*function)() = nullptr);
bool removeTask(unsigned int id = 0);

void retrivesTasksOfType(unsigned int type = 1);
void handleTaskType(unsigned int type = 1);

#endif // !