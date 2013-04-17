#include "stdafx.h"
#include "Ray.h"
#include "Camera.h"
#include "STVector3.h"
Ray::Ray(void)
{
	eye = STPoint3();
	direction = STVector3();
	minT = 0.f;
	maxT = 1000.f;
}

Ray::Ray(STPoint3 E, STPoint3 P){
	eye = E;
	direction = P - E;  
}

Ray::~Ray(void)
{
}
STPoint3 Ray::getOrigin() { return eye; }
STVector3 Ray::getDirection() { return direction; }
STPoint3 Ray::pointAlongRay(float t){
	STPoint3 P = eye + ( t * direction);
	return P;
}

STPoint3 Ray::farthestPointAlongRay() 
{
	return this->pointAlongRay(maxT);
}