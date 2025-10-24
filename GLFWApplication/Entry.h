#pragma once
#if Entry_h == 0
#define Entry_h 1 

class GLFWwindow;

struct FEngine {

	int windowWidth = 600;
	int windowHeight = 700;
	GLFWwindow* window = nullptr;
};

static void ProgramTick(float dt);
static void CreateGlfwWindow();
static void errorCallback(int error, const char* errordesc);



#endif


