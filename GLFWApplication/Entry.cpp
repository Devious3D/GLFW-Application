#if Entry_cpp == 0
#define Entry_cpp

#include <SDL3/SDL.h>
#include <GLFW/glfw3.h>

#include "Entry.h"
#include "EngineDefinitions.h"
#include "Memory.h"

using namespace Engine;

int main() {

	engineMemory = new FEngine();

	CMemoryHandler<int>* testHandle = new CMemoryHandler<int>;
	testHandle->Init(Kilobytes(sizeof(int)), 5);


	int stop = 100;
	testHandle->Insert(stop, 4);


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
	GLFWwindow* window = glfwCreateWindow(1000, 700, "Engine", NULL, NULL);

	if (window == NULL) {

		return;
	}

	print("Entry: Window is created");

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {


		ProgramTick(1.f);

		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwDestroyWindow(window);
}

void errorCallback(int error, const char* errordesc)
{
	fprintf(stderr, "Error %s\n", errordesc);

}


#endif