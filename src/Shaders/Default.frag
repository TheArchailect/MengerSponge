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

// C = La Ma + l∑fatt[Ld Md (N.L) + Ls Ms (N.H)^n]
void main()
{
    // variables
    // N
    vec3 N = normalize(Normal);
    // V
    vec3 V = normalize(Camera - Position);
    // L
    vec3 L = normalize(u_Light.Direction - Position);
    // H = L + V / |L + V| 
    vec3 H = normalize(L + V);
    // (N.H)^n
    float SpecularAngle =  pow(max(dot(H, N), 0.0), u_Material[MaterialIndex].Shininess);

    // outputs
    vec3 Ambient;
    vec3 Specular;
    float Lambertian;
    vec3 Diffuse;
    vec3 Color = vec3(0, 0, 0);

    if (LightCount != -1)
    {
        // combinations directional
        // La * Ma
        Ambient = u_Light.Ambient * u_Material[MaterialIndex].Ambient;
        // Ls * Ms * (N.H)^n
        Specular = (u_Light.Specular * u_Material[MaterialIndex].Specular) * SpecularAngle;
        // N.L
        Lambertian = max(dot(L, N), 0.0);
        // Ld * Md
        Diffuse = u_Light.Diffuse * u_Material[MaterialIndex].Diffuse * Lambertian;
        Color += Ambient + Diffuse + Specular;

        for (int i = 0; i < LightCount; ++i)
        {
            // variables
            // L
            L = normalize(u_PointLights[i].Position - Position);
            // H = L + V / |L + V| 
            H = normalize(L + V);
            // (N.H)^n
            SpecularAngle =  pow(max(dot(H, N), 0.0), u_Material[MaterialIndex].Shininess);
            float Distance = length(L);
            // 
            float Attenuation = min
            (
                1.0 / (u_PointLights[i].Constant + 
                u_PointLights[i].Linear * Distance + 
                u_PointLights[i].Quadratic * (Distance * Distance)), 
                1.0
            );
            // combinations
            // La * Ma
            Ambient = (u_PointLights[i].Ambient * u_Material[MaterialIndex].Ambient) * Attenuation;
            // Ls * Ms * (N.H)^n
            Specular = ((u_PointLights[i].Specular * u_Material[MaterialIndex].Specular) * SpecularAngle) * Attenuation;
            // N.L
            Lambertian = max(dot(L, N), 0.0);
            // Ld * Md
            Diffuse = (u_PointLights[i].Diffuse * u_Material[MaterialIndex].Diffuse * Lambertian) * Attenuation;
            Color += Ambient + Diffuse + Specular;
        }
    }
    else
    {
        Color = u_Material[MaterialIndex].Diffuse + u_Material[MaterialIndex].Ambient;
    }
    
    FragColor = vec4(Color, 1.0);
} 
