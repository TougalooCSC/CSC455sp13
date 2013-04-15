# Phase 1 Next Actions

  - [ ] Implement Scene class
    - status: started
  - [ ] Camera class
    - status: started
  - [ ] ImagePlane
    - status: started 
  - [ ] Ray Class
    - status: started 
  - [ ] Shape class
    - status: started 
  - [ ] Intersection
    - status: not-started  
  
 
 
# Log

  - Started on the camera class
     - TODO: Implement method to generate Ray from camera
	   - I think the Ray implementation needs info from ImagePlane
	   - TODO: Implement Ray class
	   - TODO: Implement ImagePlane class
	     - Start in Camera method that creates an ImagePlane
	     - Implemented method to generate Ray
     - Implement Shape classes
       - Triangle-Ray intersection
       - Sphere-Ray intersection   	
		  

# Ray Tracing Pseudocode

    Image Raytrace (Eye eye, Scene scene, int width, int height)
    {
    	Image image = new Image (width, height);
    	for (int i = 0; i < height; i++)
    		for (int j = 0; j < width; j++)
    		{
    			Ray ray = RayThruPixel (eye, i, j);
			    Intersection hit = Intersect (ray, scene);
			    image[i][j] = FindColor (hit);
    		}
    	return image;
    }
