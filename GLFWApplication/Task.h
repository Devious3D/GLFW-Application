#pragma once
#ifndef Task_h
#define Task_h

#define TASK_DELAY 1
#define TASK_AFTER RENDER 2
#define TASK_AFTER_RENDER_REPEAT 3
#define TASK_BEFORE_RENDER 4
#define TASK_BEFORE_RENDER_REPEAT 5


struct FLoggedTask {
	unsigned int type = 0;
	const void(*function);
};

void NewTask(unsigned int type, const void(*function));

#endif // !