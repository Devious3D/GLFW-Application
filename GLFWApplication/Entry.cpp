#if Entry_cpp == 0
#define Entry_cpp

#include <SDL3/SDL.h>
#include <GLFW/glfw3.h>

#include "Entry.h"
#include "Memory.h"
#include "Input.h"

using namespace Engine;

int main() {

	engine = new FEngine;
	
	CreateGlfwWindow();

	return 0;
}

static void ProgramTick(float dt)
{
	
}

void CreateGlfwWindow()
{

	if (!glfwInit()) {
		print("glfw lib uninitialized");
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	engine->MainWindow = glfwCreateWindow(engine->windowWidth, engine->windowHeight, "Engine", NULL, NULL);

	glfwSetKeyCallback(engine->MainWindow, takeKeyboardInput);


	if (engine->MainWindow == NULL) {

		Engine::print("window is nullptr");

		return;
	}

	print("Entry: Window is created");

	glfwMakeContextCurrent(engine->MainWindow);

	while (!glfwWindowShouldClose(engine->MainWindow)) {


		ProgramTick(1.f);

		glfwSwapBuffers(engine->MainWindow);
		glfwSwapInterval(1);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwDestroyWindow(engine->MainWindow);
}

void errorCallback(int error, const char* errordesc)
{
	fprintf(stderr, "Error %s\n", errordesc);

}





#endif