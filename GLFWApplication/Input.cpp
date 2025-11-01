#if Input_cpp == 0
#define Input_cpp 1

#include <GLFW/glfw3.h>

#include "Input.h"


/*
	This function detects keyboard and Mouse Inputs
*/
bool getInputPressed(int key)
{
	bool pressed = false;

	if (GLFWwindow* currentWindow = glfwGetCurrentContext()) {
		if (glfwGetKey(currentWindow, key) == GLFW_PRESS) pressed = true;
		if (glfwGetMouseButton(currentWindow, key) == GLFW_PRESS) pressed = true;
	}

	return pressed;
}

/*
	This function detects keyboard and Mouse Inputs
*/
bool getKeyEnded(int key)
{
	bool Ended = false;

	if (GLFWwindow* currentWindow = glfwGetCurrentContext()) {
		if (glfwGetKey(currentWindow, key) == GLFW_PRESS) Ended = true;
		if (glfwGetMouseButton(currentWindow, key)) Ended = true;

	}

	return Ended;
}

bool getKeyHeld(int key)
{
	bool held = false;

	if (GLFWwindow* currentWindow = glfwGetCurrentContext()) {
		if (glfwGetKey(currentWindow, key) == GLFW_REPEAT) held = true;
		if (glfwGetMouseButton(currentWindow, key)) held = true;
	}

	return held;
}

#endif

