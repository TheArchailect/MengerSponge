#version 460
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
flat in int MaterialIndex;

uniform vec3 Camera;
uniform float SystemTime;
uniform int LightCount;

struct Material {
    vec3 Ambient; 
	vec3 Diffuse;
    vec3 Specular;
	float Shininess;
};

struct DirectionalLight {
	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct PointLight {    
    vec3 Position;
    float Constant;
    float Linear;
    float Quadratic;  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};  

#define MAX_POINT_LIGHTS 100  
#define MATERIALS 3
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight u_Light;
uniform Material u_Material[MATERIALS];

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 vd)
{
    // light direction
    vec3 ld = normalize(light.Position - Position);
    // diffuse shading
    float diff = max(dot(normal, ld), 0.0);
    // specular shading
    vec3 rd = reflect(-ld, normal);
    float spec = pow(max(dot(vd, rd), 0.0), u_Material[MaterialIndex].Shininess);
    // attenuation
    float dist = length(light.Position - Position);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));    
    // combine results
    vec3 a  = light.Ambient  * u_Material[MaterialIndex].Ambient;
    vec3 d  = light.Diffuse  * diff * u_Material[MaterialIndex].Diffuse;
    vec3 s = light.Specular * spec * u_Material[MaterialIndex].Specular;
    a  *= attenuation;
    d  *= attenuation;
    s *= attenuation;
    return (a + d + s);
} 

vec3 CalculateDirectionLight(DirectionalLight light, vec3 normal, vec3 vd)
{
	// light direction
	vec3 ld = normalize(-light.Direction);
	// diffuse shading
	float diff = max(dot(normal, ld), 0.0);
	// specular projection
	vec3 rd = reflect(-ld, normal); // reflection direction
	float spec = pow(max(dot(vd, rd), 0.0), u_Material[MaterialIndex].Shininess);
	// combinations
	vec3 a = light.Ambient;
	vec3 d = light.Diffuse * diff * u_Material[MaterialIndex].Diffuse;
	vec3 s = light.Specular * spec * u_Material[MaterialIndex].Diffuse;
	return a + d + s;
}

void main()
{
	vec3 n = normalize(Normal);
	vec3 vd = normalize(Camera - Position);
	vec3 result = CalculateDirectionLight(u_Light, n, vd);
    for (int i = 0; i < LightCount; ++i)
    {
        result += CalculatePointLight(u_PointLights[i], n, vd);
    }
	FragColor = vec4(result, 1.0);
} 
