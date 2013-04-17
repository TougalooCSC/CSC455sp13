#pragma once
#include "STPoint3.h"
#include "STVector3.h"
/*
 Stores information about a ray-object intersection, such as the t value at which
the intersection occurred, the intersection point, and the normal at the intersection point.
*/
typedef struct {
	float t; // t-value at which the intersection occured
	STPoint3 P; // intersection point
	STVector3 N; // normal at the intersection point
} Intersection;