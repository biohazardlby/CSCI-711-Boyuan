#pragma once
#include "Utility.h"

class Object
{
public:
	vertex origin;
	Color color = {0,0,0};
	Color ambientColor = {0,0,.2};
	Object(vertex origin);
	~Object();
	float specular = .2f;
	float Diffuse = .5f;
	virtual bool RayTrace(Ray &ray, vertex &hit_pt, float &distance, vector &normal);
};

class Sphere : public Object {
public:
	float radius;
	Sphere(vertex origin, float radius);
	bool RayTrace(Ray &ray, vertex &hit_pt, float &distance, vector &normal) override;
};
class Triangle : public Object {
public:
	vertex v0, v1, v2;
	Triangle(vertex v0, vertex v1, vertex v2);
	bool RayTrace(Ray &ray, vertex &hit_pt, float &distance, vector& normal) override;
};