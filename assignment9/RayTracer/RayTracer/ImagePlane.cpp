#include "StdAfx.h"
#include "ImagePlane.h"

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
