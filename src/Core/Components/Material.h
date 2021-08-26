#pragma once
#include "Core/include.h"
class Material {
public:
	Material(float a[], float d[], float s[], float shininess)
	{
		for (int i = 0; i < 4; ++i)
		{
			Ka[i] = a[i];
			Kd[i] = d[i];
			Ks[i] = s[i];
		}
		n[0] = shininess;
	}
	GLfloat Ka[4];
	GLfloat Kd[4];
	GLfloat Ks[4];
	GLfloat n[1];
};