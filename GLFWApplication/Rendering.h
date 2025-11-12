#pragma once
#ifndef Rendering_h
#define Rendering_h 1
#define basicRendering 1



static unsigned int VertexBufferObject;

static float SampleVerticies[] = {
    //x      y     z
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};




static unsigned int CreateShaderProgram();
static unsigned int CompileShader(unsigned int type, const char* sourcePath);
static void SetUpRender();
void MainRender(float dt);


#endif