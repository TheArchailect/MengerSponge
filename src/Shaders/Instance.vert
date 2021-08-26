#version 460 core
layout (location = 0) in vec3 Position0;
layout (location = 1) in mat4 M;
out mat4 Model;
void main(void) {
	Model = M;
	gl_Position = vec4(Position0 , 1.0);
}