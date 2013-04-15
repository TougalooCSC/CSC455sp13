#ifndef CAMERA_H
#define CAMERA_H

#include "st.h"
#include "rtForward.h"
#include "ImagePlane.h"
class Camera {
	
public:
	Camera();
	Camera( const STPoint3&, const STVector3&, const STPoint3&, float, float);
	Camera( const Camera&);
	Camera& operator=(const Camera&);
	ImagePlane createImagePlane();
	ImagePlane getImagePlane();
	void setImagePlane(ImagePlane p);
	Ray rayThruPixel(int, int);
	
private:
	STPoint3 eye;
	STVector3 up;
	STPoint3 lookingAt;
	ImagePlane plane;
	float fovy;
	float aspect;

};

#endif CAMERA_H