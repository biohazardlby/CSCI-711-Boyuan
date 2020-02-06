#pragma once
#include "Ray.h"
#include "Utility.h"

class Object
{
public:
	vertex origin;
	Color color;
	Object(vertex origin);
	~Object();
	virtual bool RayTrace(Ray &ray, vertex &hit_pt, float &distance);
};

class Sphere : public Object {
public:
	float radius;
	Sphere(vertex origin, float radius);
	bool RayTrace(Ray &ray, vertex &hit_pt, float &distance);
};
class Triangle : public Object {
public:
	vertex v0, v1, v2;
	Triangle(vertex v0, vertex v1, vertex v2);
	bool RayTrace(Ray &ray, vertex &hit_pt, float &distance);
};