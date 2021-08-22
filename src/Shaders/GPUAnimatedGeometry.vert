#version 460 core
layout (location = 0) in vec3 Position0;
layout (location = 1) in vec3 Position1;

uniform float SystemTime;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

#ifndef HALF_PI
#define HALF_PI 1.5707963267948966
#endif

float elasticIn(float t) {
  return sin(13.0 * t * HALF_PI) * pow(2.0, 10.0 * (t - 1.0));
}

#ifndef PI
#define PI 3.141592653589793
#endif

float sineInOut(float t) {
  return -0.5 * (cos(PI * t) - 1.0);
}


float bounceOut(float t) {
  const float a = 4.0 / 11.0;
  const float b = 8.0 / 11.0;
  const float c = 9.0 / 10.0;

  const float ca = 4356.0 / 361.0;
  const float cb = 35442.0 / 1805.0;
  const float cc = 16061.0 / 1805.0;

  float t2 = t * t;

  return t < a
    ? 7.5625 * t2
    : t < b
      ? 9.075 * t2 - 9.9 * t + 3.4
      : t < c
        ? ca * t2 - cb * t + cc
        : 10.8 * t * t - 20.52 * t + 10.72;
}

void main(void) {
	float AnimationTime = map(cos(SystemTime/1000), -1, 1, 0, 1);
    AnimationTime = sineInOut(AnimationTime);
	vec3 interpolatedPosition = AnimationTime * Position0 + (1 - AnimationTime) * Position1;
	gl_Position = vec4(interpolatedPosition, 1.0);
    //gl_Position = vec4(Position1 , 1.0);
}