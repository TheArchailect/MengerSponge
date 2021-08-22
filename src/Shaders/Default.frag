#version 460
// out
out vec4 FragColor;
// in
in vec3 Normal;
in vec3 Position;
// global
vec3 LightPosition = vec3(0, 20, 0);
// uniform
uniform vec3 Camera;
uniform float SystemTime;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	vec3 color = vec3(1.0, 1.0, 1.0);
	// ambient
	vec3 ambient = 0.08 * color;
	// diffuse
	vec3 lightDirection = normalize(LightPosition - Position);
	vec3 normal = normalize(Normal);
	float diff = max(dot(lightDirection, normal), 0.0);
	vec3 diffuse = diff * color;
	
	// specular
	vec3 viewDirection = normalize(Camera - Position);
	//vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specular = 0.0;
	// blinn
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	specular = pow(max(dot(normal, halfwayDirection), 0.0), 64);
	vec3 spec = vec3(0.3) * specular;
	FragColor = vec4(ambient + diffuse + spec, 1.0);
} 
