#pragma once

#include <iostream>
#include <vector>

class GLFWwindow;

struct InputEvent;

namespace Engine {


	struct Vector2 {

	};

	struct Vector3 {

	};

	struct FEngine {

		const int windowWidth = 1000;
		const int windowHeight = 700;
		GLFWwindow* MainWindow = nullptr;

		std::vector<InputEvent> inputEvents;
	};


#define cast static_cast
#define dynCast dynamic_cast

#define Bytes(n) (n)
#define Kilobytes(n) (1024 * Bytes(n))
#define Megabytes(n) (1024 * Kilobytes(n))
#define Gigabytes(n) (1024 * Megabytes(n))

	static inline void ThrowError(const char* msg) {
		std::cout << "(Error) | " << msg << std::endl;
		return throw;
	}

	static void print(const char* msg) {
		std::cout << msg << std::endl;
	}

	static void print(int msg) {
		std::cout << msg << std::endl;
	}

	static void print(float msg) {
		std::cout << msg << std::endl;
	}

	static void print(double msg) {
		std::cout << msg << std::endl;
	}
}


static Engine::FEngine* engine = nullptr;

static void ProgramTick(float dt);
static void CreateGlfwWindow();
static void errorCallback(int error, const char* errordesc);



