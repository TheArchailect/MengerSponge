#pragma once
#include "Core/include.h"
#include "Math.h"

static glm::vec3 CubicSphereCast(glm::vec3 origin, glm::vec3 point, float radius)
{
	float HalfCubeSize = 10.0f;
	float PointIntersectionDiff = HalfCubeSize / glm::max(abs(point.x), glm::max(abs(point.y), abs(point.z)));
	glm::vec3 IntersectionPoint = point * PointIntersectionDiff;
	float IntersectionLength = glm::distance(origin, IntersectionPoint);
	float Ratio = glm::distance(origin, point) / IntersectionLength;
	float PointDiff = (radius * Ratio) / glm::length(point);
	if (PointDiff < 1.0f)
	{
		return point * PointDiff;
	}
	else SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "something went wrong with sphere cast");
	return point;
}

static glm::vec3 SphericalDistribution()
{
	glm::vec3 v(0, 0, 0);
	double theta = 0;
	double phi = 0;
	theta = 2 * M_PI * RandomFloat(0, 1);
	phi = acos(2 * RandomFloat(0, 1) - 1.0f);
	v.x = cos(theta) * sin(phi);
	v.y = sin(theta) * sin(phi);
	v.z = cos(phi);
	return v;
}