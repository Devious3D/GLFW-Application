#if Entry_cpp == 0
#define Entry_cpp 1



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw.h"
#include "ImGui\imgui_impl_opengl3.h"

#include "Input.h" 
#include "Rendering.h"
#include "Timer.h"
#include "UI.h"

#include "EngineConfig.h"

#include "Entry.h" // Engine Definitions




using namespace Engine;

FEngine* engine;

#if IsSinglePlayer
FClient* client;
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
	engine->renderer = new Renderer;

	client = new FClient;


	CreateGlfwWindow("Engine", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, nullptr);

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

	//Main Processes //Running processes according to load

	{
		//Run delay tasks functions

		//HandleTimers(dt);

		//Before-Render

		MainRender(dt);
		uiMain(dt);

		//After-Render
		
	}

	return false;
}


void CreateGlfwWindow(const char* WindowName, const int windowWidth, const int windowHeight, void(*functionCallback)())
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

	if (engine->MainWindow == NULL) ThrowError("window is nullptr");
	glfwMakeContextCurrent(engine->MainWindow);

	if (glewInit() != GLEW_OK) ThrowError(std::string("(Entry): GLEW failed to load"));

	print(std::string(WindowName) + std::string(" window is Created"));
	if (functionCallback) functionCallback();
		
	ImGui::StyleColorsClassic();	

	if (engine->MainWindow) {
		ImGui_ImplGlfw_InitForOpenGL(engine->MainWindow, true);
		ImGui_ImplOpenGL3_Init();
	}
	else throw std::runtime_error("Window is not created?");

	//Change this with render class
	renderStart();

	engine->renderer = new Renderer();
	engine->renderer->setProgram(deleteLater_basicProg);

	auto currentTime = std::chrono::high_resolution_clock::now();
	auto previousTime = currentTime;
	
	while (!glfwWindowShouldClose(engine->MainWindow)) {

		currentTime = std::chrono::high_resolution_clock::now();

		//#1
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (imGuiIo.WantCaptureMouse) engine->inputsLocked = true;
		else engine->inputsLocked = false;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//#2
		//Ui Should be able to render at this point
		engine->engineState = EngineState::running;

		bool shouldClose = ProgramTick(engine->deltatime);
		if (shouldClose) {
			engine->engineState = EngineState::closing;
			break;
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//#3
		glfwSwapBuffers(engine->MainWindow);
		glfwSwapInterval(1);
		glfwPollEvents();


		engine->deltatime = -(std::chrono::duration<float>(previousTime - currentTime).count());
		previousTime = currentTime;

		engine->engineTime += engine->deltatime;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	glfwDestroyWindow(engine->MainWindow);
}


void errorCallback(int error, const char* errordesc)
{
	for (int i = 0; i < glfwErrorsToIgnore.size(); i++) {
		if (error == glfwErrorsToIgnore[i]) continue;
		if (getEngine()->engineState == EngineState::closing) break;
		
		ThrowError(errordesc);
		break;
	}
}

Engine::FEngine* getEngine()
{
	return engine;
}

Engine::FClient* GetClient()
{
	return client;
}


#endif