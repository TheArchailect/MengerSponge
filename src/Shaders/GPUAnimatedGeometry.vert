#version 460 core
layout (location = 0) in vec3 Position0;
layout (location = 1) in vec3 Position1;

uniform float SystemTime;

float Map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float ease(float t) {
	return t * t * t;
}

void main(void) {
	float AnimationTime = Map(cos(SystemTime/1000), -1, 1, 0, 1);
    AnimationTime = ease(AnimationTime);
	vec3 interpolatedPosition = AnimationTime * Position0 + (1 - AnimationTime) * Position1;
	gl_Position = vec4(interpolatedPosition, 1.0);
}
