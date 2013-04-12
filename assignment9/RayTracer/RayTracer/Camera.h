#ifndef CAMERA_H
#define CAMERA_H

#include "st.h"
#include "rtForward.h"
class Camera {
	
public:
	Camera();
	Camera( const STPoint3&, const STVector3&, const STPoint3&, float, float);
	Camera( const Camera&);
	ImagePlane createImagePlane();
	Ray rayThruPixel(int, int);
	Camera& operator=(const Camera&);
private:
	STPoint3 eye;
	STVector3 up;
	STPoint3 lookingAt;
	float fovy;
	float aspect;

};

#endif CAMERA_H