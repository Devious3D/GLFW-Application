#pragma once
#if Input_h == 0
#define Input_h 1 

class GLFWwindow;

struct InputEvent {
	int key;
	int action;
	float timePressed;
};

void takeKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void clearInputs();

#endif