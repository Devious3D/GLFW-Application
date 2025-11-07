#if Entry_cpp == 0
#define Entry_cpp 1


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include "Entry.h"
#include "Memory.h"
#include "Input.h"
#include "Rendering.h"
#include "Timer.h"

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw.h"
#include "ImGui\imgui_impl_opengl3.h"

using namespace Engine;

Engine::FEngine* engine;

#if IsSinglePlayer
Engine::FClient* client;
#endif

int main() {
	using namespace std;

	if (!glfwInit()) 
	{
		ThrowError("GLFW failed to init");
		return -1;
	}
	else
	{
		print("GLFW is Loaded");
	}


	engine = new FEngine;
	client = new FClient; 

	FTimer* timer = newTimer(1, 0, ETimerType::TickDown, ETimerActionOnCompletion::Repeat);

	CreateGlfwWindow("Engine", engine->windowWidth, engine->windowHeight);

	return 0;
}


static bool ProgramTick(float dt)
{

	{
		if (getInputPressed(GLFW_KEY_ESCAPE)) {
			return true;
		}

		if (client != nullptr) {

			glfwGetCursorPos(glfwGetCurrentContext(), &client->mousePos.x, &client->mousePos.y);
		}
	}

	//Main Processes
	{
		HandleTimers(dt);
		MainRender(dt);
	}

	return false;
}


void CreateGlfwWindow(const char* WindowName, const int windowWidth, const int windowHeight)
{

	glfwSetErrorCallback(errorCallback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& imGuiIo = ImGui::GetIO();
	imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	engine->MainWindow = glfwCreateWindow(windowWidth, windowHeight, WindowName, NULL, NULL);

	if (engine->MainWindow == NULL) {
		ThrowError("window is nullptr");
		return;
	}

	glfwMakeContextCurrent(engine->MainWindow);

	if (glewInit() != GLEW_OK) ThrowError(std::string("(Entry): GLEW failed to load"));
	else print(std::string("(Entry): GLEW is loaded"));

	print(std::string(WindowName) + std::string(" window is Created"));


	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(engine->MainWindow, true);
	ImGui_ImplOpenGL3_Init();


	auto currentTime = std::chrono::high_resolution_clock::now();
	auto previousTime = currentTime;
	
	while (!glfwWindowShouldClose(engine->MainWindow)) {

		currentTime = std::chrono::high_resolution_clock::now();

		//#1
		glClear(GL_COLOR_BUFFER_BIT);

		if (imGuiIo.WantCaptureMouse) engine->inputsLocked = true;
		else engine->inputsLocked = false;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//#2
		//Ui Should be able to render at this point
		bool shouldClose = ProgramTick(engine->deltatime);
		if (shouldClose) break;

		ImGui::Begin("Engine Panel");
		
		if (ImGui::CollapsingHeader("Information")) {
				
			ImGui::BulletText((std::string("Mouse Pos: ") + client->mousePos.tostring()).c_str());

		}

		ImGui::End();
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//#3
		glfwPollEvents();
		glfwSwapBuffers(engine->MainWindow);
		glfwSwapInterval(1);

		engine->deltatime = -(std::chrono::duration<float>(previousTime - currentTime).count());
		previousTime = currentTime;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwTerminate();
	glfwDestroyWindow(engine->MainWindow);

	delete engine;
	delete client;
}


void errorCallback(int error, const char* errordesc)
{
	for (int i = 0; i < glfwErrorsToIgnore.size(); i++) {
		if (error == glfwErrorsToIgnore[i]) continue;
		
		ThrowError(errordesc);
		break;
	}
}

Engine::FEngine* GetEngine()
{
	return engine;
}

Engine::FClient* GetClient()
{
	return client;
}


#endif