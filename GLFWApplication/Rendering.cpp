#ifndef Rendering_cpp
#define Rendering_cpp 1

#include <GL/glew.h>

#include "Rendering.h"
#include "Entry.h"

#include "EngineDefinitions.h"

using namespace Engine;
static uint CreateShaderProgram()
{
	uint program = glCreateProgram();
	uint vert = 0;
	uint frag = 0;

	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vert);
	glDeleteShader(frag);
	
	return program;
}

static uint CompileShader(unsigned int type, const char* sourcePath)
{
	uint shader = glCreateShader(type);

	glGetShaderSource(shader, 1, NULL, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		
		int msgLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msgLength);
		char* msg = (char*)(std::to_string(msgLength).c_str());
		glGetShaderInfoLog(shader, msgLength, &msgLength, msg);
		ThrowError(std::string(msg));
	}



	return uint();
}

static void SetUpRender() {
		
	glGenBuffers(1, &VertexBufferObject); // creat the Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); // Select the Buffer
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), SampleVerticies, GL_STATIC_DRAW); // Putting data in the buffer
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); // Telling OpenGL what to read

}

void MainRender(float dt)
{
	//if (FEngine* Engine = GetEngine()) {
	//	print(std::to_string(Engine->deltatime));
	//}

	

}


#endif


