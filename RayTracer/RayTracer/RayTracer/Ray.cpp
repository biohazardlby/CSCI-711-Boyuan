#include "Ray.h"


Ray::Ray(vertex origin, vector direction, float length)
{
	this->origin = origin;
	this->direction = direction;
	this->length = length;
}

Ray::Ray(vertex origin, vector direction)
{
	this->origin = origin;
	this->direction = direction;
}

Ray::~Ray()
{
}
