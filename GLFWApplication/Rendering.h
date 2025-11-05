#pragma once
#ifndef Rendering_h
#define Rendering_h 1


struct Triangle {
	unsigned int buffer = 0;
    const float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
};


void MainRender(float dt);


#endif