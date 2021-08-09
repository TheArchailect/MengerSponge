#version 460
out vec4 FragColor;
in vec3 CameraPosition;
in vec3 OutNormal;
in vec3 OutPosition;
uniform float SystemTime;
vec3 LightPosition = vec3(0, 0, 0);

#ifndef PI
#define PI 3.141592653589793
#endif

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec4 Diffuse() {
	// Attenuation
	
	vec3 lightDirection = normalize(LightPosition - OutPosition);
	vec4 DiffuseMat;
	vec3 TempNormal = abs(OutNormal);
	if (TempNormal.x > TempNormal.y && TempNormal.x > TempNormal.z)
	{
		DiffuseMat = vec4(0.780392f, 0.568627f, 0.113725f, 1.0f);
	}
	else if (TempNormal.y > TempNormal.z && TempNormal.y > TempNormal.x) 
	{
		DiffuseMat = vec4(0.55f,0.55f,0.55f,1.0f);
	}
	else if (TempNormal.z > TempNormal.x && TempNormal.z > TempNormal.y) 
	{
		DiffuseMat = vec4(0.18275f, 0.17f, 0.22525f, 0.82f);
	}
	float diff = max(dot(lightDirection, OutNormal), 0.0);
	
	vec3 viewDirection = normalize(CameraPosition - OutPosition);
	vec3 reflectionDirection = reflect(-lightDirection, OutNormal);
	
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float specular = pow(max(dot(OutNormal, halfwayDirection), 0.0), 256);
	vec3 spec = vec3(1) * specular;
	vec3 ambient = 0.08 * DiffuseMat.xyz;
	vec3 Output = ambient + (diff * DiffuseMat.xyz) + spec;

	return vec4(Output, 1);
}

void main() {
	FragColor = Diffuse();
}