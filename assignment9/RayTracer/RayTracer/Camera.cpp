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
	STVector3 w = a; w.Normalize(); // get the unit view vector
	STVector3 u = STVector3::Cross(b,w); u.Normalize(); // get the right hand view unit vector
	STVector3 v = STVector3::Cross(w,u);
	STPoint3 C = eye + w;
	double y = tan(fovy/2.0);
	double x = tan(aspect * fovy / 2.0);
	STPoint3 ll, ul, lr, ur;
	ll = C + (x * u) - (y * v);
	ul = C + (x * u) + (y * v);
	lr = C - (x * u) - (y * v);
	ur = C - (x * u) + (y * v);
	return ImagePlane(ll, ul, lr, ur);
}
Ray Camera::rayThruPixel(int, int)
{	
	return Ray();
}