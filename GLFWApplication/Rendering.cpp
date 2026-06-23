#ifndef Rendering_cpp
#define Rendering_cpp 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Rendering.h" //<string>, <vector>, RenderMath
#include "Entry.h" // Memory.h



std::string parseShaderFromFile(const char* filePath)
{
	using namespace std;

	ifstream file(filePath);
	stringstream inStream;

	string line;
	while (getline(file, line)) {
		inStream << line << "\n";
	}


	return inStream.str();
}

void renderStart()
{
#if basicRendering

	const char* basic_Frag = "Shaders/BasicShader/Basic_frag.frag";
	const char* basic_Vert = "Shaders/BasicShader/Basic_vert.vert";

	deleteLater_basicProg = ShaderProgram(basic_Vert, basic_Frag);

	
#elif


#endif
}




void MainRender(float dt)
{
	using namespace std;

	if (Engine::FEngine* engine = getEngine()) {
		switch (engine->wireFrameMode) {
		case true: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case false: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}



#if basicRendering

	//Vertex p1;
	//p1.position = { 0.f, -.5f, 0.f };

	//Vertex p2;
	//p2.position = { -1.f, -.5f, 0.f };

	//Vertex p3;
	//p3.position = { -.5f, 0.5f, 0.f };
	

	Renderer* renderer = getEngine()->renderer;

	Quad test_quad;

	for (Vector::Vertex vert : test_quad.verticies) {
		vert.setGlData();
		for (float componentVal : vert.glData) {
			//cout << "Component: " << componentVal << endl;
			renderer->verticies.push_back(componentVal);
		}

	}

	const void *vertsRaw = renderer->verticies.data();

	//const float vertsRaw_deref = *vertsRaw;
	//cout << verticies << endl;

	   
	uint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * renderer->verticies.size(), vertsRaw, GL_STATIC_DRAW);

	uint ElementBuffer;
	glGenBuffers(1, &ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);;



	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float) ));
	glEnableVertexAttribArray(1);

	
	//double engineTime = getEngine()->engineTime;
	//float greenValue = sin(engineTime) / 2.f + .5f;
	//int vertexColorLocation = glGetUniformLocation(deleteLater_basicProg.getProgram(), "finalColor");
	//glUniform4f(vertexColorLocation, 0.f, greenValue, 0.f, 1.f);


	glUseProgram(deleteLater_basicProg.getProgram());
	glBindVertexArray(buffer);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	renderer->verticies.clear();

#elif

#endif

	/*if (FEngine* Engine = getEngine()) {
		std::cout << "Delta time:" << std::to_string(Engine->deltatime) << std::endl;
	}*/
}



uint ShaderProgram::compileShader(unsigned int type, const char* path)
{
	uint newShader = glCreateShader(type);
	std::string shaderCode = parseShaderFromFile(path);
	const char* code_to_char = shaderCode.c_str();

;	std::cout << shaderCode << std::endl;

	glShaderSource(newShader, 1, &code_to_char, nullptr);
	glCompileShader(newShader);

	//debug
	int success;
	char info[512];
	glGetShaderiv(newShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(newShader, 512, NULL, info);

		if (type == GL_VERTEX_SHADER) std::cout << "Vertex Shader Error" << std::endl;
		else std::cout << "Fragment Shader Error" << std::endl;
		
		std::cout << info << std::endl;
		throw std::runtime_error("Shader Compile Error");
		//cout << "Shader compile error: " << info << endl;
	}

	return newShader;
}

ShaderProgram::ShaderProgram(const char* vertSource, const char* fragSource)
{
	this->program = glCreateProgram();

	//std::cout << "Program ID: " << program << std::endl;

	this->vert = this->compileShader(GL_VERTEX_SHADER, vertSource);
	this->frag = this->compileShader(GL_FRAGMENT_SHADER, fragSource);

	glAttachShader(this->program, this->vert);
	glAttachShader(this->program, this->frag);
	glLinkProgram(this->program);

	glDeleteShader(this->vert);
	glDeleteShader(this->frag);


	int progSucc;
	char info[512];
	glGetProgramiv(this->program, GL_LINK_STATUS, &progSucc);
	if (!progSucc) {
		glGetProgramInfoLog(this->program, 512, NULL, info);
		std::cout << info << std::endl;
		throw std::runtime_error("Shader link Error");
	}

	std::cout << "Shader Created" << std::endl;
}

ShaderProgram::~ShaderProgram()
{
	std::cout << "Shader destruction" << std::endl;
}



Renderer::~Renderer()
{
}

void Renderer::setProgram(ShaderProgram prog)
{
	this->currProgram = prog;
}



#endif


