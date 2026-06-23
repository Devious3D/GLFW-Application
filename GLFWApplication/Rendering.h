#pragma once
#ifndef Rendering_h
#define Rendering_h 1

#define basicRendering 1

#include <string>
#include <vector>

#include "EngineDefinitions.h"


class ShaderProgram;
class Renderer;
class Quad;
class RenderObject;

static unsigned int VertexBufferObject;
const float SampleVerticies[] = {
    //x      y     z
    -1.f, -.5f, 0.0f,
    0.f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,

    .5f,  .5f, 0.0f,
    1.f, -.5f, 0.0f,
    0.0f -.5f, 0.0f
};

const float QuadVerticies[] = {
    .5f, -.5f, 0.f,
    -.5f, -.5f, 0.f,
    -.5f, .5f, 0.f,
    .5f, .5f, 0.f
};

const unsigned int indicies[]{
    0, 1, 3,
    1, 2, 3
};


//

class Quad {
public:

    

    Vector::Vertex verticies[4]{
        Vector::Vertex(.5f, -.5f, 0.f),
        Vector::Vertex(-.5f, -.5f, 0.f),
        Vector::Vertex(-.5f, .5f, 0.f),
        Vector::Vertex(.5f, .5f, 0.f)
    };

    Quad() {}
};


class ShaderProgram {

private:

    unsigned int program = 0;
    unsigned int vert = 0;
    unsigned int  frag = 0;

    unsigned int compileShader(unsigned int type, const char* path);

public:

    ShaderProgram() {}
    ShaderProgram(const char* vertSource, const char* fragSource);
    ~ShaderProgram();

    unsigned int getProgram() const {
        return this->program;
    }

};


class Renderer {

private:

    unsigned int elementBuf;
    unsigned int vertexBuf;
    ShaderProgram currProgram;
    //std::vector<Vertex, std::allocator<Vertex>, > verticies;

public:

    //Create the Buffers
    //Bind the data
    //Enabled the vertex inputs
    //Then Draw


    void bufferData() {

    }

    void inputData() {

    }

    Renderer() {}
    ~Renderer();



    void setProgram(ShaderProgram prog);
    size_t size();

};




//
_declspec(selectany) ShaderProgram deleteLater_basicProg;

std::string parseShaderFromFile(const char* filePath);
void renderStart();
void MainRender(float dt);


#endif