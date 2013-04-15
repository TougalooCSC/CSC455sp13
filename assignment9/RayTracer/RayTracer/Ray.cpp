#include "stdafx.h"
#include "Ray.h"
#include "Camera.h"

Ray::Ray(void)
{
	eye = STPoint3();
	direction = STVector3();
	minT = 0.f;
	maxT = 1000.f;
}

Ray::Ray(STPoint3 e, int u, int v){
	eye = e;
	//direction =  
}

Ray::~Ray(void)
{
}
