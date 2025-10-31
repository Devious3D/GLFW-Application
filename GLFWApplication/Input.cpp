#if Input_cpp == 0
#define Input_cpp 1

#include <GLFW/glfw3.h>

#include "Input.h"
#include "Entry.h"

void takeKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	switch (action) {

	case GLFW_PRESS:
		
		InputEvent event;
		event.action = action;
		event.key = key;



		Engine::print("Key Pressed");

		break;

	case GLFW_RELEASE:

		Engine::print("Key Released");

		break;

	case GLFW_REPEAT:

		Engine::print("Key Held");

		break;
	}

	
}

void clearInputs()
{
}

#endif