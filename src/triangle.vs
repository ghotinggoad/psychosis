#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main(){
    gl_Position = vec4(aPos, 1.0f); // gl_Position, contains the position of the current vertex, think &pointer that points to a vec4 data in memory.
    ourColor = aColor;
}