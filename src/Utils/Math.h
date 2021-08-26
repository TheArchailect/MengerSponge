#pragma once
#include "Core/include.h"

static float Map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

static float RandomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float x = max - min;
	float result = random * x;
	return min + result;
}

//	Easings By Robert Penner
//	https://github.com/glslify/glsl-easings
static float SineInOut(float t)
{
	return -0.5 * (cos(M_PI * t) - 1.0);
}

static float exponentialInOut(float t) {
    return t == 0.0 || t == 1.0
        ? t
        : t < 0.5
        ? +0.5 * pow(2.0, (20.0 * t) - 10.0)
        : -0.5 * pow(2.0, 10.0 - (t * 20.0)) + 1.0;
}

