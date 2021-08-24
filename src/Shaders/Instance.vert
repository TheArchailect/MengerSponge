#version 460 core
layout (location = 0) in vec3 Position0;

uniform mat4 M[9];
out mat4 Models;

void main(void) {
	Models = M[gl_InstanceID];
	gl_Position = vec4(Position0, 1.0);
}