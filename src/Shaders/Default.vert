#version 460 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
out vec3 OutNormal;
out vec3 CameraPosition;
out vec3 OutPosition;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main(void) {
	OutNormal = mat3(transpose(inverse(Model))) * Normal;
	CameraPosition = (inverse(View) * vec4(0,0,0,1)).xyz;
	OutPosition = (Model * vec4(Position, 1.0)).xyz;
	gl_Position = Projection * View * Model * vec4(Position, 1.0);
}