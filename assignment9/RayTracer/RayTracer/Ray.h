#pragma once
#include "st.h"
#include "rtForward.h"
#include "STPoint3.h"
/*
	Represents a ray dened by the equation e+td, where e is the ray's starting point and d is
the direction the ray points in. Rays should also carry information about the minimum and maximum
t value for which intersections with the ray are considered valid.
*/
class Ray
{
public:
	Ray(void);
	Ray(STPoint3, int, int);
	~Ray(void);

private:
	STPoint3 eye;
	STVector3 direction;
	float minT;
	float maxT;

};
