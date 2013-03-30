#include "sgl.h"
#include "st.h"
#include <stack>
#include <iostream>
using namespace std;
// --- Do not modify this code ---+
#define IMPLEMENT_THIS_FUNCTION printf("Warning: call to unimplemented function!\n")
STImage* img;
int buffer_width;
int buffer_height;
void setBuffer(STImage* ptr) { img = ptr; }
void setBufferSize(int w, int h) { buffer_width = w; buffer_height = h; }
// --- End of do not modify this code ---+
class Triangle{

public:
	STPoint3 v1;
	STPoint3 v2;
	STPoint3 v3;
	Triangle(STPoint3, STPoint3, STPoint3);
};

Triangle::Triangle(STPoint3 vert1, STPoint3 vert2, STPoint3 vert3) 
{
	v1 = vert1;
	v2 = vert2;
	v3 = vert3;
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
vector<STPoint3> vertex_buffer;
vector<STColor3f> color_buffer;
STColor3f current_color;
//For computing the bounding box
float min_x, min_y, max_x, max_y;

void makeTrianglesV1(vector<STPoint3> vertices, vector<Triangle> &triangles) {
	//cout << "\t# of Triangles before: " << triangles.size() << endl;
	for(int i = 0; i < vertices.size() - 2; i++){
		triangles.push_back(Triangle(vertices[i], vertices[i+1], vertices[i+2]));
	}

	//cout << "\t# of Triangles after: " << triangles.size() << endl;
}
void fragment(int x, int y) {
	//Ver. 1 - just fill the pixel
	img->SetPixel(x,y,STImage::Pixel(current_color));
}
void rasterizeTriangle(Triangle t){
	Line line0(t.v1, t.v2);
	Line line1(t.v2, t.v3);
	Line line2(t.v3, t.v1);
	float e0 = 1.0, e1 = 1.0, e2 = 1.0;
	for (int y = 0; y < buffer_height; y++){
		for (int x = 0; x < buffer_width; x++){
			e0 = line0.a * x + line0.b * y + line0.c;
			e1 = line1.a * x + line1.b * y + line1.c;
			e2 = line2.a * x + line2.b * y + line2.c;
			if (e0 <= 0 && e1 <= 0 && e2 <= 0)
			{	
				fragment(x,y);
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
	STPoint3 point = current_matrix.multiply(STPoint3(x, y, 1.0f));
	//2. Insert into Vertex Buffer
	vertex_buffer.push_back(point);
	//3. Insert Current Color in Color Buffer
	color_buffer.push_back(current_color);
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
