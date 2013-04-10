#pragma once
#include "st.h"
class Ray
{
public:
	Ray(void);
	Ray(Camera eye, int, int);
	~Ray(void);

private:
	STPoint3 eye;
	STVector direction;
	float minT;
	float maxT;

};
