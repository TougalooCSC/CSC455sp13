#include "stdafx.h"
#include "Scene.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Camera.h"


Scene::Scene(std::string sceneFilename)
{
	Parse(sceneFilename);
	this->max_t = 1000.0;
}

void Scene::Parse(std::string sceneFilename)
{
	BeganParsing();

	std::ifstream sceneFile(sceneFilename.c_str());

	// Die if we couldn't find the file
	if (sceneFile.fail())
	{
		printf("Scene::Parse - Could not find input scene file '%s'\n", sceneFilename.c_str());
		exit(1);
	}
	//else
	//	printf("All systems are go!\n");
	//this->outputfilename = sceneFilename;
	//this->outputfilename

	char line[1024];
	while (!sceneFile.eof())
	{
		sceneFile.getline(line, 1023);
		std::stringstream ss;
		ss.str(line);
		std::string command;
		ss >> command;

		if (command == "Camera")
		{
			float ex, ey, ez, ux, uy, uz, lx, ly, lz, f, a;
			ss >> ex >> ey >> ez >> ux >> uy >> uz >> lx >> ly >> lz >> f >> a;
			STPoint3 eye(ex, ey, ez);
			STVector3 up(ux, uy, uz);
			STPoint3 lookAt(lx, ly, lz);
			ParsedCamera(eye, up, lookAt, f, a);
		}
		else
		if (command == "Output")
		{
			int w, h;
			std::string fname;
			ss >> w >> h >> fname;
			ParsedOutput(w, h, fname);
		}
		else
		if (command == "BounceDepth")
		{
			int depth;
			ss >> depth;
			ParsedBounceDepth(depth);
		}
		else if (command == "ShadowBias")
		{
			float bias;
			ss >> bias;
			ParsedShadowBias(bias);
		}
		else
		if (command == "PushMatrix")
		{
			ParsedPushMatrix();
		}
		else
		if (command == "PopMatrix")
		{
			ParsedPopMatrix();
		}
		else
		if (command == "Rotate")
		{
			float rx, ry, rz;
			ss >> rx >> ry >> rz;
			ParsedRotate(rx, ry, rz);
		}
		else
		if (command == "Scale")
		{
			float sx, sy, sz;
			ss >> sx >> sy >> sz;
			ParsedScale(sx, sy, sz);
		}
		else
		if (command == "Translate")
		{
			float tx, ty, tz;
			ss >> tx >> ty >> tz;
			ParsedTranslate(tx, ty, tz);
		}
		else
		if (command == "Sphere")
		{
			float cx, cy, cz, r;
			ss >> cx >> cy >> cz >> r;
			STPoint3 center(cx, cy, cz);
			ParsedSphere(center, r);
		}
		else
		if (command == "Triangle")
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			STPoint3 v[3];
			v[0] = STPoint3(x1, y1, z1);
			v[1] = STPoint3(x2, y2, z2);
			v[2] = STPoint3(x3, y3, z3);
			ParsedTriangle(v[0], v[1], v[2]);
		}
		else
		if (command == "AmbientLight")
		{
			float r, g, b;
			ss >> r >> g >> b;
			STColor3f col(r, g, b);
			ParsedAmbientLight(col);
		}
		else
		if (command == "PointLight")
		{
			float px, py, pz, r, g, b;
			ss >> px >> py >> pz >> r >> g >> b;
			STPoint3 pos(px, py, pz);
			STColor3f col(r, g, b);
			ParsedPointLight(pos, col);
		}
		else
		if (command == "DirectionalLight")
		{
			float dx, dy, dz, r, g, b;
			ss >> dx >> dy >> dz >> r >> g >> b;
			STVector3 dir(dx, dy, dz);
			STColor3f col(r, g, b);
			ParsedDirectionalLight(dir, col);
		}
		else
		if (command == "Material")
		{
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs >> bs >> rr >> gr >> br >> shine;
			STColor3f amb(ra, ga, ba);
			STColor3f diff(rd, gd, bd);
			STColor3f spec(rs, gs, bs);
			STColor3f mirr(rr, gr, br);
			ParsedMaterial(amb, diff, spec, mirr, shine);
		}
	}
	sceneFile.close();

	FinishedParsing();
}

void Scene::BeganParsing()
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::FinishedParsing()
{
	/** CS 148 TODO: Fill this in **/
	this->render();
	this->frame->Save("Output.png");
	
}


void Scene::ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect)
{
	/** CS 148 TODO: Fill this in **/
	this->camera = Camera(eye,up,lookAt,fovy,aspect);
}

void Scene::ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename)
{
	/** CS 148 TODO: Fill this in **/
	this->frame = new STImage(imgWidth, imgHeight);
	//this->frame.Initialize(imgWidth, imgHeight);
}

void Scene::ParsedBounceDepth(int depth)
{
	/** CS 148 TODO: Fill this in **/
}
void Scene::ParsedShadowBias(float bias)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedPushMatrix()
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedPopMatrix()
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedRotate(float rx, float ry, float rz)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedScale(float sx, float sy, float sz)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedTranslate(float tx, float ty, float tz)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedSphere(const STPoint3& center, float radius)
{
	/** CS 148 TODO: Fill this in **/
	Sphere s(center,radius);
	this->spheres.push_back(s);
}

void Scene::ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedAmbientLight(const STColor3f& col)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedPointLight(const STPoint3& loc, const STColor3f& col)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedDirectionalLight(const STVector3& dir, const STColor3f& col)
{
	/** CS 148 TODO: Fill this in **/
}

void Scene::ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine)
{
	/** CS 148 TODO: Fill this in **/
}
bool cmp_intersection(Intersection &a, Intersection &b)
{
	return a.t < b.t;	
}

void Scene::setMaxT(float max){
	this->max_t = max;
}
Intersection Scene::findIntersection( Ray ray)
{
	std::vector<Intersection> hits;
	float t = 0.0;
	for(std::vector<Sphere>::iterator sphere_it = this->spheres.begin(); sphere_it != this->spheres.end(); ++sphere_it)
	{
		if(sphere_it->doesItIntersect(ray, t)){
			Intersection hit; 
			hit.t = t;
			hit.P = ray.getOrigin() + t * ray.getDirection();
			STVector3 hit_normal = hit.P - sphere_it->getCenter();
			hit_normal.Normalize();
			hit.N = hit_normal;
			hits.push_back(hit);
		}
	}
	
	// If we find no hits, then the ray goes off into infinity or max_t
	if (hits.size() == 0)
	{
		Intersection no_hit;
		no_hit.t = Scene::max_t+1.0;
		return no_hit;
	}
	else{
		//Find the Intersection with the minimum t value
		std::vector<Intersection>::iterator result = std::min_element(hits.begin(), hits.end(), cmp_intersection);
		return *result;
	}
}
void Scene::render()
{
	int width = this->frame->GetWidth();
	int height = this->frame->GetHeight();
	for (int i = 0; i < height; i++)
	{	
		for (int j = 0; j < width; j++)
		{
			Ray ray = this->camera.rayThruPixel(i,j);
			Intersection hit = this->findIntersection(ray);
			if ( hit.t < this->max_t )
				this->frame->SetPixel(i,j,STImage::Pixel(STColor3f(0.0)));
			else
				this->frame->SetPixel(i,j,STImage::Pixel(STColor3f(1.0)));
		}

	}
}