#include "stdafx.h"
#include "Shape.h"
#include "Ray.h"
#include "STVector3.h"
#include "Intersection.h"

Triangle::Triangle(STPoint3 v0, STPoint3 v1, STPoint3 v2) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
}
bool Triangle::doesItIntersect(Ray r, float &t){
	return false;
}

Sphere::Sphere(STPoint3 center, float radius) {
	this->center = center;
	this->radius = radius;
}
STPoint3 Sphere::getCenter() { return center; }
bool Sphere::doesItIntersect(Ray r, float &t) {
	STPoint3 O = r.getOrigin(); 
	STVector3 D = r.getDirection();
	//STPoint3 X1 = r.farthestPointAlongRay();
	float a = STVector3::Dot(D,D);
	float b = 2 * STVector3::Dot( STVector3(O - center), STVector3(O));
	float c = STVector3::Dot(STVector3(O - center), STVector3(O - center)) - (radius * radius);
	
	float disc = b * b - 4 * a * c;
	
	if (disc < 0)
		return false;

	float distSqrt = sqrtf(disc);
	float q;
	if ( b < 0)
		q = (-b - distSqrt)/2.0;
	else
		q = (-b + distSqrt)/2.0;

	float t0 = q / a;
	float t1 = c / q;
	
	if (t0 > t1)
	{
		t = t1;
		return true;
	}
	else
	{
		t = t0;
		return true;
	}
}