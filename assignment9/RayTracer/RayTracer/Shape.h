#pragma once
/*
	An abstract class that represents a geometric primitive in the scene. It 
	should at least have a method for determining whether a given ray intersects 
	with it. You'll want to have subclasses that represent specic shapes, such 
	as Spheres and Triangles.
*/
#include "rtForward.h"
#include "st.h"
#include "Ray.h"

class Shape
{
public:
	virtual bool doesItIntersect(Ray, float&) = 0;
};

class Triangle : public Shape
{
public:
	Triangle(STPoint3, STPoint3, STPoint3);
	bool doesItIntersect(Ray, float& );
private:
	STPoint3 v0, v1, v2;
};

class Sphere : public Shape
{
public:
	Sphere(STPoint3, float);
	bool doesItIntersect(Ray, float&);
private:
	STPoint3 center;
	float radius;
};

