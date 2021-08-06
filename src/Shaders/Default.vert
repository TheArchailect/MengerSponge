#version 460 core
layout(location = 0) in vec3 position;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 out_position;

void main() {
    gl_Position = Projection * View * Model * vec4(position, 1.0);
    out_position = position;
}