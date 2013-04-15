#pragma once
#include "st.h"
/*
	class ImagePlane: Represents a virtual 'window' into the scene. 
	This class should be able to sample itself at discrete pixel locations 
	(using bilinear interpolation). It should also store the colors that result
	from tracing rays through those sample points, and it should be able to 
	write the stored results to an image file.
*/
class ImagePlane
{
public:
	
	ImagePlane(void);
	ImagePlane(STPoint3, STPoint3, STPoint3, STPoint3);
	~ImagePlane(void);
private:
	STPoint3 LL, LR, UL, UR; // Coordinates for the 4 corners of the image plane	

};
