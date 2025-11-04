#if Entry_cpp == 0
#define Entry_cpp 1


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "Entry.h"
#include "Memory.h"
#include "Input.h"
#include "Rendering.h"

using namespace Engine;

int main() {
	using namespace std;

	if (!glfwInit()) {
		ThrowError(string("GLFW failed to init"));
		return -1;
	}


	engine = new FEngine;
	client = new Client; 

	CreateGlfwWindow("Engine", engine->windowWidth, engine->windowHeight);

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

	if (client != nullptr) {

		glfwGetCursorPos(glfwGetCurrentContext(), &client->mousePos.x, &client->mousePos.y);
	}

	//Main Processes
	MainRender(dt);
}


void CreateGlfwWindow(const char* WindowName, const int windowWidth, const int windowHeight)
{
	using namespace std;

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	engine->MainWindow = glfwCreateWindow(windowWidth, windowHeight, WindowName, NULL, NULL);


	if (engine->MainWindow == NULL) {

		print("window is nullptr");

		return;
	}

	print(string(WindowName) + string(" window is Created"));

	glfwMakeContextCurrent(engine->MainWindow);


	if (glewInit() != GLEW_OK) 
	{
		ThrowError(string("(Entry): GLEW failed to load"));
	}
	else
	{
		print(string("(Entry): GLEW is loaded"));
	}

	auto currentTime = chrono::steady_clock::now();
	auto previousTime = currentTime;
	
	while (!glfwWindowShouldClose(engine->MainWindow)) {

		currentTime = chrono::steady_clock::now();

		ProgramTick(1.f);

		if (engine == nullptr) break;

		glfwSwapBuffers(engine->MainWindow);
		glfwSwapInterval(1);
		glfwPollEvents();

		engine->deltatime = chrono::duration<float, std::milli>(previousTime - currentTime).count();
		previousTime = currentTime;

		print(to_string(engine->deltatime));
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

		ThrowError(errordesc);
		break;
	}
}

#endif