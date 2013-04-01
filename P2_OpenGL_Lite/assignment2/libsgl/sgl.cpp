#include "sgl.h"
#include "st.h"
#include <stack>
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include "STColor4ub.h"
using namespace std;
// --- Do not modify this code ---+
#define IMPLEMENT_THIS_FUNCTION printf("Warning: call to unimplemented function!\n")
STImage* img;
int buffer_width;
int buffer_height;
void setBuffer(STImage* ptr) { img = ptr; }
void setBufferSize(int w, int h) { buffer_width = w; buffer_height = h; }
// --- End of do not modify this code ---+
//Added a class to encapsulate STPoint3 objects along with attributes
class SGLPoint3 : public STPoint3
{
public:
	STColor3f c;
	SGLPoint3() : STPoint3() {}
	SGLPoint3(float x, float y, float z) : STPoint3(x,y,z)
	{}
	SGLPoint3(float x, float y, float z, STColor3f color) : STPoint3(x,y,z)
	{	c = color; }
	SGLPoint3(STPoint3 pt) : STPoint3(pt.x, pt.y, pt.z) {}
};

class Triangle{

public:
	SGLPoint3 v1;
	SGLPoint3 v2;
	SGLPoint3 v3;
	Triangle(SGLPoint3, SGLPoint3, SGLPoint3);
	string toString();
};

Triangle::Triangle(SGLPoint3 vert1, SGLPoint3 vert2, SGLPoint3 vert3) 
{
	v1 = vert1;
	v2 = vert2;
	v3 = vert3;
}

string Triangle::toString() { 
		char str_rep[200];
		sprintf(str_rep, "v1{%f, %f, %f} \nv2{%f, %f, %f} \nv3{%f, %f, %f}\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
		return string(str_rep);
	}

class Line {
public:
	float a;
	float b;
	float c;
	Line(STPoint3, STPoint3);
};

Line::Line(STPoint3 v0, STPoint3 v1) {
	a = v1.y - v0.y;
	b = v0.x - v1.x;
	c = -(a * v0.x + b * v0.y);
}
stack<STTransform3> matrix_stack;
STTransform3 current_matrix;
vector<SGLPoint3> vertex_buffer;
vector<STColor3f> color_buffer;
STColor3f current_color;
//For computing the bounding box
double min_x, min_y, max_x, max_y;

void makeTrianglesV1(vector<SGLPoint3> vertices, vector<Triangle> &triangles) {
	//cout << "\t# of Triangles before: " << triangles.size() << endl;
	vector<SGLPoint3> vert_copy(vertices.size());
	copy(vertices.begin(), vertices.end(), vert_copy.begin());
	int j, j_prv, j_nxt;
	size_t nSize = vertices.size();
	//for(int i = 0; i < nSize - 2; i++){
	while (nSize > 2)
	{
		j = 0;
		j_nxt = (j+1)%nSize;
		j_prv = (j+(nSize-1))%nSize;
		triangles.push_back(Triangle(vert_copy[j], vert_copy[j_nxt], vert_copy[j_prv]));
		vert_copy.erase(vert_copy.begin());
		nSize = vert_copy.size();
	}

	//cout << "\t# of Triangles after: " << triangles.size() << endl;
}
void fragment(int x, int y, STColor4ub c) {
	//Ver. 1 - just fill the pixel
	img->SetPixel(x,y,c);
}
//For handling singularities (edges that touch pixels)
int shadow( Line l) {
	return (l.a > 0) || (l.a == 0 && l.b > 0);
}
int inside( float e, Line l) {
	return (e == 0) ? !shadow(l) : (e < 0);
}
struct BoundingBox {
	float xmin;
 	float xmax;
	float ymin;
	float ymax;
};

void bound3( Triangle t, BoundingBox &b ) {
	b.xmin = ceil(min(min(t.v1.x, t.v2.x), t.v3.x));
	b.xmax = ceil(max(max(t.v1.x, t.v2.x), t.v3.x));
	b.ymin = ceil(min(min(t.v1.y, t.v2.y), t.v3.y));
	b.ymax = ceil(max(max(t.v1.y, t.v2.y), t.v3.y));
}
void interpolateColor(Triangle t)
{
}
SGLPoint3 normalize(SGLPoint3 v){
	double x = (v.x - min_x)/(max_x - min_y);
	double y = (v.y - min_y)/(max_y - min_y);
	SGLPoint3 p(x,y,1);
	p.c = v.c;
	return p;
}	
double areaFunction(STPoint3 v0, STPoint3 v1, STPoint3 v){
	SGLPoint3 p0 = normalize(v0);
	SGLPoint3 p1 = normalize(v1);
	SGLPoint3 p = normalize(v);
	return (p0.y - p1.y)*p.x + (p1.x - p0.x)*p.y + p0.x*p1.y - p1.x*p0.y;
}
void rasterizeTriangle(Triangle t){
	Line line0(t.v1, t.v2);
	Line line1(t.v2, t.v3);
	Line line2(t.v3, t.v1);
	BoundingBox b;
	bound3(t, b);
	printf("x (min, max) (%f, %f)\ny (min, max) (%f, %f)\n", 
		b.xmin, b.xmax, b.ymin, b.ymax);
	cout << t.toString() << endl;
	float e0 = 1.0, e1 = 1.0, e2 = 1.0;
	float red, green, blue;
	float area_1_2 = areaFunction(t.v2, t.v3, t.v1);
	float area_2_0 = areaFunction(t.v3, t.v1, t.v2);
	float area_0_1 = areaFunction(t.v1, t.v2, t.v3);
	float alpha, beta, gamma;
	printf("a_12: %f, a_20: %f, a_01: %f\n", area_1_2, area_2_0, area_0_1);

	for (int y = b.ymin; y < b.ymax; y++){
		for (int x = b.xmin; x < b.xmax; x++){
			e0 = line0.a * x + line0.b * y + line0.c;
			e1 = line1.a * x + line1.b * y + line1.c;
			e2 = line2.a * x + line2.b * y + line2.c;
			if (inside(e0,line0) && inside(e1,line1) && inside(e2,line2))
			{	
				//STColor4ub c;
				//c.a = 1.f;
				alpha = areaFunction(t.v2, t.v3, STPoint3(x,y,1));
				beta = areaFunction(t.v3, t.v1, STPoint3(x,y,1));
				gamma = areaFunction(t.v1, t.v2, STPoint3(x,y,1));
				//red = -e0*t.v1.c.r -e1*t.v2.c.r - e2*t.v3.c.r;
				//green = -e0*t.v1.c.g - e1*t.v2.c.g - e2*t.v3.c.g;
				//blue = -e0*t.v1.c.b - e1*t.v2.c.b - e2*t.v3.c.b;
				red   = alpha*t.v1.c.r + beta*t.v2.c.r + gamma*t.v3.c.r;
				green = alpha*t.v1.c.g + beta*t.v2.c.g + gamma*t.v3.c.g;
				blue  = alpha*t.v1.c.b + beta*t.v2.c.b + gamma*t.v3.c.b;
				fragment(x,y,STColor4ub(STColor3f(red,green,blue),255));
			}
		}	
	}
}
void renderTriangles()
{
	cout << "# of Vertices: " << vertex_buffer.size() << endl;
	//IMPLEMENT_THIS_FUNCTION;
	// 1. Make Triangles
	vector <Triangle> triangles;
	cout << "# of Triangles before: " << triangles.size() << endl;
	makeTrianglesV1(vertex_buffer, triangles);
	vector<Triangle>::iterator triangleIterator;
	for(triangleIterator = triangles.begin(); triangleIterator != triangles.end(); triangleIterator++)
	{
		//cout << (*triangleIterator).toString();
		rasterizeTriangle(*triangleIterator);	
	}
	cout << "# of Triangles after: " << triangles.size() << endl;
	// 2. Detect Fragments
	// 3. Determine Fragment Color
}
void sglBeginTriangles()
{
	//IMPLEMENT_THIS_FUNCTION;
	// Empty vertex and color buffers
	if (!vertex_buffer.empty())
	{
		vertex_buffer.erase(vertex_buffer.begin(), vertex_buffer.end());
		color_buffer.erase(color_buffer.begin(), color_buffer.end());
		min_x = min_y = max_x = max_y = 0.0f;
	}
}

void sglEnd()
{
	//IMPLEMENT_THIS_FUNCTION;
	renderTriangles();
}

void sglLoadIdentity()
{
	float ident[3][3] =	{	{1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{0.0, 0.0, 1.0}
						};
	current_matrix = STTransform3(ident);

}

void sglScale(SGLfloat xscale, SGLfloat yscale)
{
	IMPLEMENT_THIS_FUNCTION;
}

void sglTranslate(SGLfloat xtrans, SGLfloat ytrans)
{
	IMPLEMENT_THIS_FUNCTION;
}

void sglRotate(SGLfloat angle)
{
	IMPLEMENT_THIS_FUNCTION;
}

void sglPushMatrix()
{
	IMPLEMENT_THIS_FUNCTION;
}

void sglPopMatrix()
{
	IMPLEMENT_THIS_FUNCTION;
}

void sglVertex(SGLfloat x, SGLfloat y)
{
	//IMPLEMENT_THIS_FUNCTION;
	//1. Apply Transforms
	SGLPoint3 point(current_matrix.multiply(SGLPoint3(x, y, 1.0f)));
	point.c = current_color;
	//2. Insert into Vertex Buffer
	vertex_buffer.push_back(point);
	//3. Insert Current Color in Color Buffer
	//color_buffer.push_back(current_color);
	
	if (point.x < min_x)
		min_x = point.x;
	if (point.x > max_x)
		max_x = point.x;
	if (point.y < min_y)
		min_y = point.y;
	if (point.y > max_y)
		max_y = point.y;
}

void sglColor(SGLfloat r, SGLfloat g, SGLfloat b)
{
	current_color = STColor3f(r,g,b);
}
