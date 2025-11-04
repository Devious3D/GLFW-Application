#pragma once

#define IsSinglePlayer 1
#define IsMultiplayer 1

#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>

class GLFWwindow;

namespace Engine {

	#define cast static_cast
	#define dynCast dynamic_cast

	#define Bytes(n) (n)
	#define Kilobytes(n) (1024 * Bytes(n))
	#define Megabytes(n) (1024 * Kilobytes(n))
	#define Gigabytes(n) (1024 * Megabytes(n))

	struct Client;
	struct Vector2;
	struct Vector3;
	struct FEngine;



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
		const int windowWidth = 1000;
		const int windowHeight = 700;
		float deltatime = 0.f;
	};

	struct Client {
		Vector2 mousePos;
		int FPS = 0;
	};

	static inline void ThrowError(std::string msg) {
		std::cout << "(Error) | " << msg << std::endl;
		return throw;
	}

	static void print(std::string msg) {
		std::cout << msg << std::endl;
	}
}


static Engine::FEngine* engine = nullptr;

#if IsSinglePlayer
static Engine::Client* client = nullptr;
#endif



static void ProgramTick(float dt);
static void CreateGlfwWindow(const char* WindowName, const int windowWidth, const int windowHeight);
static void errorCallback(int error, const char* errordesc);