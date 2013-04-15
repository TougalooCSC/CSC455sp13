#include "StdAfx.h"
#include "ImagePlane.h"
#include "STPoint3.h"

ImagePlane::ImagePlane(void)
{
}

ImagePlane::ImagePlane(STPoint3 ll, STPoint3 ul, STPoint3 lr, STPoint3 ur){
	LL = ll;
	UL = ul;
	LR = lr;
	UR = ur;
}

ImagePlane::~ImagePlane(void)
{
}

void ImagePlane::setWidth(int w) { width = w; }
void ImagePlane::setHeight(int h) { height = h; }
int ImagePlane::getWidth() { return width; }
int ImagePlane::getHeight() { return height; }

STPoint3 ImagePlane::getImagePlanePosition(int x, int y){
	STVector3 P;
	STVector3 ll(LL), ul(UL), lr(LR), ur(UR);
	float dx = (lr.x - ll.x) / width;
	float dy = (ul.y - ll.y) / height;
	// reference: http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtexamp1.htm
	float u = ll.x + 0.5 * dx + x * dx;
	float v = ul.y + 0.5 * dy + y * dy;
	P = (1 - u)*((1 - v)*ll + v*ul) + (u) * ((1-v)*lr + v*ur);
	STPoint3 p(P);
	return p;
}
