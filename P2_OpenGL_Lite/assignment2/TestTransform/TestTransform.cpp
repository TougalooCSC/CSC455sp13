// TestTransform.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "st.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	STTransform3 xform;
	float identM[3][3] = {{1, 0, 0},
							{0, 1, 0},
							{0, 0, 1}};
	float scale_x2M[3][3] = {{2, 0, 0},
							{0, 2, 0},
							{0, 0, 1}};
	STTransform3 identity(identM);
	STTransform3 scale2(scale_x2M);
	float translate_M[3][3] = {	{1, 0, 1},
								{0, 1, 1},
								{0, 0, 0}};
	STTransform3 translateXform(translate_M);
	STPoint3 point(1,1,1);
	cout << point.x << " " << point.y << " " << point.z << " " << endl;
	STPoint3 p2 = xform.multiply(point);
	cout << p2.x << " " << p2.y << " " << p2.z << " " << endl;
	STPoint3 p3 = identity.multiply(point);
	cout << p3.x << " " << p3.y << " " << p3.z << " " << endl;
	STPoint3 p4 = scale2.multiply(point);
	cout << p4.x << " " << p4.y << " " << p4.z << " " << endl;
	STPoint3 p5 = translateXform.multiply(point);
	cout << p5.x << " " << p5.y << " " << p5.z << " " << endl;
	system("pause");
	return 0;
}

