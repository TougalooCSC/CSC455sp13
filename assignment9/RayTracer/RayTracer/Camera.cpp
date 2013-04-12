#include "stdafx.h"
#include "Camera.h"
#include "ImagePlane.h"
#include "Ray.h"




Camera::Camera(){
	eye = STPoint3(0.f, 0.f, 0.f);
	up = STVector3(0.f, 1.f, 0.f);
	lookingAt = STPoint3(0.f, 0.f, 0.f);
	aspect = 1.0;
	fovy = 90.0;
}

Camera::Camera(const STPoint3 &eyePosition, const STVector3 &upVector, const STPoint3 &lookingAtCoord, float fovUp, float aspectRatio){
	eye = eyePosition;
	up = upVector;
	lookingAt = lookingAtCoord;
	fovy = fovUp;
	aspect = aspectRatio;
}

Camera::Camera( const Camera& src){
	eye = src.eye;
	up = src.up;
	lookingAt = src.lookingAt;
	fovy = src.fovy;
	aspect = src.aspect;
}


Camera& Camera::operator =( const Camera &rhs ) {
	eye = rhs.eye;
	up = rhs.up;
	lookingAt = rhs.lookingAt;
	fovy = rhs.fovy;
	aspect = rhs.aspect;
	return *this;
}

ImagePlane Camera::createImagePlane(){
	STVector3 b = up;
	STVector3 a = lookingAt - eye;
	return ImagePlane();
}
Ray Camera::rayThruPixel(int, int)
{
	return Ray();
}