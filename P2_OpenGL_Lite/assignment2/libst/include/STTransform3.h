// STColor3f.h
#ifndef __STTRANSFORM3_H__
#define __STTRANSFORM3_H__

// Forward-declare libst types.
#include "stForward.h"

/**
*  Class representing a 3x3 matrix that can be used to
*  apply transforms to 2D points and vectors
*/
class STTransform3
{
	// Fill in your class definition here. STTransform3 should implement a 3x3 matrix that
	// you can use to modify 2D vertices with homogenous coordinates (hence the 3x3 size
	// rather than 2x2). This class doesn't need to be complicated. Other than basic 
	// accessor functions, you'll probably want to implement multiplication between transforms.
	// You have a lot of flexibility as to how you implement this class, but you will need to
	// follow the conventions used in the rest of libst.
private:
	float _M[3][3];

public:
	STTransform3();
	STTransform3(float);
	STTransform3(float [3][3]);
	STTransform3(STVector3, STVector3, STVector3);

	STPoint3 multiply(STPoint3);
	STTransform3 multiply(const STTransform3, const STTransform3);

};

//STPoint3 operator*(const STPoint3& left, const STVector3& right);
//STTransform3 operator*(const STTransform3& left, const SSTransform3& right);

#endif