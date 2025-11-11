#ifndef EngineUI_cpp
#define EngineUI_cpp 

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "ImGui\imgui.h"

#include "Entry.h"

#include "EngineUI.h"


void MainEnginePanel()
{
	ImGui::Begin("Engine");

	//Engine and Dependency Versions
	if (ImGui::CollapsingHeader("Info")) {
		using namespace std;

		ImGui::SeparatorText("Backends Versions");

		const string engineVersion = string("Engine version: ") +
			to_string(ENGINE_VERSION_MAJOR) + string(".") +
			to_string(ENGINE_VERSION_MINOR);
		ImGui::BulletText(engineVersion.c_str());

		const string glfwVersion = string("GLFW version: ") + glfwGetVersionString();
		ImGui::BulletText(glfwVersion.c_str());


		int major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		const string glVerion = string("OpenGL version: ") +
			to_string(major) + string(".") + to_string(minor);

		ImGui::BulletText(glVerion.c_str());
	}

	ImGui::End();
}

#endif
