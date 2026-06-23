//basic_frag
#version 330 core

out vec4 fragColor;

uniform vec4 finalColor;


void main() {
    fragColor = finalColor;
}