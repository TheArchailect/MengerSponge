#version 460 core
layout (location = 0) in vec3 Position0;

uniform vec3 offsets[9];

void main(void) {

	gl_Position = vec4(Position0 + offsets[gl_InstanceID], 1.0);
}