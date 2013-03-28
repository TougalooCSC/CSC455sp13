#include "sgl.h"
#include "st.h"
#include <stack>
using namespace std;
// --- Do not modify this code ---+
#define IMPLEMENT_THIS_FUNCTION printf("Warning: call to unimplemented function!\n")
STImage* img;
int buffer_width;
int buffer_height;
void setBuffer(STImage* ptr) { img = ptr; }
void setBufferSize(int w, int h) { buffer_width = w; buffer_height = h; }
// --- End of do not modify this code ---+

stack<STTransform3> matrix_stack;
STTransform3 current_matrix;
vector<STPoint3> vertex_buffer;
vector<STColor3f> color_buffer;
STColor3f current_color;
//For computing the bounding box
float min_x, min_y, max_x, max_y;

void renderTriangles()
{
	IMPLEMENT_THIS_FUNCTION;
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
	IMPLEMENT_THIS_FUNCTION;
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
