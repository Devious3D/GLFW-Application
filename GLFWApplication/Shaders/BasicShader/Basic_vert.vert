//basic_vert
#version 330 core

//the max amount of attributes is 16 and up to 4-components in each attribute

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aColor;

out vec4 finalColor;
 
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    finalColor = vec4(aColor.x, aColor.y, aColor.z, 1.0f);
}