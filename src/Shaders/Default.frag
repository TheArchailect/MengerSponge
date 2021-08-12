#version 460
// out
out vec4 FragColor;
// in
in vec3 Normal;
in vec3 Position;
// global
vec3 LightPosition = vec3(0, 0, 0);
// uniform
uniform vec3 Camera;
uniform float SystemTime;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	vec3 Color = vec3(0.5, 0.1, 0.3);
	vec3 Ambient = 0.05 * Color;
	vec3 LightDirection = normalize(LightPosition - Position);
	vec3 normal = normalize(Normal);
	float Diff = max(dot(LightDirection, normal), 0.0);
	vec3 Diffuse = Diff * Color;
	vec3 ViewDirection = normalize(Camera - Position);
	float specular = 0.0;
	vec3 HalfwayDirection = normalize(LightDirection + ViewDirection);
	specular = pow(max(dot(normal, HalfwayDirection), 0.0), 128);
	vec3 Spec = vec3(1) * specular;
	FragColor = vec4(Ambient + Diffuse + Spec, 1);
} 
