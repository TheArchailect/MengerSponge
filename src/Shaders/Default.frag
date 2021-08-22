#version 460
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 Camera;
uniform float SystemTime;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

struct Material {
	vec3 Diffuse;
	float Shininess;
};

struct DirectionalLight {
	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

uniform DirectionalLight u_Light;
uniform Material u_Material;

vec3 CalculateDirectionLight(DirectionalLight light, vec3 normal, vec3 vd)
{
	// light direction
	vec3 ld = normalize(-light.Direction);
	// diffuse shading
	float diff = max(dot(normal, ld), 0.0);
	// specular projection
	vec3 rd = reflect(-ld, normal); // reflection direction
	float spec = pow(max(dot(vd, rd), 0.0), u_Material.Shininess);
	// combinations
	vec3 a = light.Ambient;
	vec3 d = light.Diffuse * diff * u_Material.Diffuse;
	vec3 s = light.Specular * spec * u_Material.Diffuse;
	return a + d + s;
}

void main()
{
	vec3 n = normalize(Normal);
	vec3 vd = normalize(Camera - Position);
	vec3 result = CalculateDirectionLight(u_Light, n, vd);
	FragColor = vec4(result, 1.0);
} 
