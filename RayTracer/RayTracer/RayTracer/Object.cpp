#include "Object.h"



Object::Object(vertex origin)
{
	this->origin = origin;
}


Object::~Object()
{

}

bool Object::RayTrace(Ray & ray, vertex & hit_pt, float &distance, vector& normal)
{
	return false;
}

Sphere::Sphere(vertex origin, float radius) : Object(origin)
{
	this->radius = radius;
}

// Sphere //
bool Sphere::RayTrace(Ray &ray, vertex &hit_pt, float &distance, vector& normal)
{
	vector oc = ray.origin - this->origin;
	float a = dot(ray.direction, ray.direction);
	float b = 2.0 * dot(oc, ray.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	hit_pt = ray.origin + ray.direction * ((-b - sqrt(discriminant)) / (2 * a));
	normal = normalize(hit_pt - this->origin);
	distance = ((-b - sqrt(discriminant)) / (2 * a));
	return (discriminant > 0 && (-b - discriminant > 0));
}

// Polygon //

Triangle::Triangle(vertex v0, vertex v1, vertex v2) : Object(v0)
{
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
}

bool Triangle::RayTrace(Ray & ray, vertex & hit_pt, float & distance, vector& normal)
{
//MOLLER_TRUMBORE 
	vector v0v1 = v1 - v0;
	vector v0v2 = v2 - v0;
	vector pvec = cross(ray.direction,v0v2);
	float det = dot(v0v1,pvec);
	float t, u, v;
// CULLING 
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < 0.00) return false;

	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < kEpsilon) return false;

	float invDet = 1 / det;

	vector tvec = ray.origin - v0;
	u = dot(tvec,pvec) * invDet;
	if (u < 0 || u > 1) return false;

	vector qvec = cross(tvec,v0v1);
	v = dot(ray.direction,qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = dot(v0v2,qvec) * invDet;
	
	hit_pt = v0 + u * v0v1 + v * v0v1;
	distance = length(hit_pt - ray.origin);
	normal = normalize(cross(v0v1, v0v2));
	return true;
}
