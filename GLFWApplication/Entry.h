#pragma once
#if Entry_h == 0
#define Entry_h 1 

class GLFWwindow;

template<typename T>
class MemoryHandler;

struct FEngine {

	int windowWidth = 600;
	int windowHeight = 700;
	GLFWwindow* window = nullptr;
};

FEngine* engineMemory = nullptr;

static void ProgramTick(float dt);
static void CreateGlfwWindow();
static void errorCallback(int error, const char* errordesc);



#endif


