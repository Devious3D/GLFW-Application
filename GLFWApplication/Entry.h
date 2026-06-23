#pragma once
#ifndef Entry_h 
#define Entry_h

#include "Memory.h" // Engine Definitions


#define DEFAULT_WINDOW_WIDTH 1000
#define DEFAULT_WINDOW_HEIGHT 700
#define ENGINE_VERSION_MAJOR 0
#define ENGINE_VERSION_MINOR 0

struct FTimer;
class GLFWwindow;
class Renderer;


namespace Engine {

	struct Client;
	struct Vector2;
	struct Vector3;
	struct FEngine;

	enum class EngineState : int {
		none = -1,
		running = 0,
		closing = 1
	};

	static const std::vector<int> glfwErrorsToIgnore = {
		65539
	};

	struct Vector2 {
		double x = 0.f;
		double y = 0.f;

		std::string tostring() {
			using namespace std;

			return string("X: ") + to_string(x)
				+ string(" Y: ") + to_string(y);
		}
	};

	struct Vector3 {
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		std::string tostring() {
			using namespace std;

			return string("X: ") + to_string(x)
				+ string(" Y: ") + to_string(y)
				+ string(" Z: ") + to_string(z);
		}
	};


	struct FEngine {

		GLFWwindow* MainWindow = nullptr;
		Renderer* renderer;

		EngineState engineState = EngineState::none;
		float deltatime = 0.f;
		double engineTime = 0.00f;
		bool inputsLocked = false;
		bool wireFrameMode = false;
	};

	struct FClient {
		Vector2 mousePos;
		int FPS = 0;
	};
}


static bool ProgramTick(float dt);
static void CreateGlfwWindow(
	const char* WindowName, 
	const int windowWidth,
	const int windowHeight,
	void(*callbackfun)()
);

static void errorCallback(int error, const char* errordesc);
Engine::FEngine* getEngine();
Engine::FClient* GetClient();



#endif