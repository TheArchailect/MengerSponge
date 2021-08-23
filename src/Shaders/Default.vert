#version 460 core
layout (location = 0) in vec3 Position0;

void main(void) {
	gl_Position = vec4(Position0 , 1.0);
}