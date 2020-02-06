#pragma once
#include "Utility.h"
class Ray
{
public:
	vertex origin;
	vector direction;
	float length = 0;

	Ray(vertex origin, vector direction, float length);
	Ray(vertex origin, vector direction);
	~Ray();
};

