//basic_frag
#version 330 core

in vec4 finalColor;
out vec4 fragColor;
//uniform vec4 finalColor;


void main() {
    fragColor = finalColor;
}