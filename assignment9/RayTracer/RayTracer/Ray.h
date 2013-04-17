#pragma once
#include "st.h"
#include "rtForward.h"
#include "STPoint3.h"
#include "STVector3.h"
#include "ImagePlane.h"
/*
	Reprsents a ray defined by the equation e+td, where e is the ray's 
	starting point and d is the direction the ray points in. Rays should also 
	carry information about the minimum and maximum t value for which 
	intersections with the ray are considered valid.
*/
class Ray
{
public:
	Ray(void);
	Ray(STPoint3, STPoint3);
	~Ray(void);
	STPoint3 getOrigin();
	STVector3 getDirection();
	STPoint3 pointAlongRay(float t);
	STPoint3 farthestPointAlongRay();

private:
	STPoint3 eye;
	STVector3 direction;
	ImagePlane plane;
	float minT;
	float maxT;

};
