#include "stdafx.h"
#include "Shape.h"
#include "Ray.h"

Triangle::Triangle(STPoint3 v0, STPoint3 v1, STPoint3 v2) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
}
bool Triangle::doesItIntersect(Ray r){
	return false;
}

Sphere::Sphere(STPoint3 center, float radius) {
	this->c = center;
	this->radius = radius;
}

bool Sphere::doesItIntersect(Ray r) {
	return false;
}