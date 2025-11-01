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
	if (engine == nullptr) return;
	if (engine->MainWindow == nullptr) return;


	if (getInputPressed(GLFW_KEY_ESCAPE)) {
		glfwTerminate();
		glfwDestroyWindow(engine->MainWindow);

		delete engine;
		engine = nullptr;

		return;
	}
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


	if (engine->MainWindow == NULL) {

		Engine::print("window is nullptr");

		return;
	}

	print("Entry: Window is created");

	glfwMakeContextCurrent(engine->MainWindow);

	while (!glfwWindowShouldClose(engine->MainWindow)) {


		ProgramTick(1.f);

		if (engine == nullptr) break;

		glfwSwapBuffers(engine->MainWindow);
		glfwSwapInterval(1);
		glfwPollEvents();
	}

	if (engine) {
		glfwTerminate();
		glfwDestroyWindow(engine->MainWindow);
	}
}

void errorCallback(int error, const char* errordesc)
{
	for (int i = 0; i < glfwErrorsToIgnore.size(); i++) {
		if (error == glfwErrorsToIgnore[i]) continue;

		fprintf(stderr, "Error %s\n", errordesc);
		break;
	}
}





#endif