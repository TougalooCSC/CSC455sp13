#ifndef SCENE_H
#define SCENE_H

#include "st.h"
#include "raytrace.h"
#include "Camera.h"
#include "ImagePlane.h"
#include "Ray.h"
#include "Intersection.h"
#include "Shape.h"
#include <vector>

class Scene
{
public:
	Scene(std::string sceneFilename);

	/** CS 148 TODO: Add methods for the scene to render itself, etc. **/
	Intersection findIntersection(Ray);
	void render();
	void setMaxT(float);

private:

	/** Parsing helpers **/
	void Parse(std::string sceneFilename);
	void BeganParsing();
	void FinishedParsing();
	void ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect);
	void ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename);
	void ParsedBounceDepth(int depth);
	void ParsedShadowBias(float bias);
	void ParsedPushMatrix();
	void ParsedPopMatrix();
	void ParsedRotate(float rx, float ry, float rz);
	void ParsedScale(float sx, float sy, float sz);
	void ParsedTranslate(float tx, float ty, float tz);
	void ParsedSphere(const STPoint3& center, float radius);
	void ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3);
	void ParsedAmbientLight(const STColor3f& col);
	void ParsedPointLight(const STPoint3& loc, const STColor3f& col);
	void ParsedDirectionalLight(const STVector3& dir, const STColor3f& col);
	void ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine);

	/** CS 148 TODO: Add instance vars to store camera, lights, objects, etc. **/
	Camera camera;
	STImage *frame;
	std::vector<Sphere> spheres;
	std::vector<Triangle> triangles;
	float max_t;
	std::string outputfilename;

};


#endif SCENE_H

