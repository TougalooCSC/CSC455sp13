// STTransform3.cpp
#include "STTransform3.h"
#include "STPoint3.h"

// Fill in your implementation of STTransform here.
STTransform3::STTransform3(){
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_M[i][j] = 0.0;
}

STTransform3::STTransform3(float b[3][3]){
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_M[i][j] = b[i][j];
}

STTransform3::STTransform3(STVector3 X, STVector3 Y, STVector3 Z){
	STVector3 rows[3] = { X, Y, Z};
	for (int i = 0; i < 3; i++)
		for(int j = 0; j < 0; j++)
			_M[i][j] = rows[i].Component(j);

}
//TODO: fix incorrect order of operands when multiplying a point and a matrix
STPoint3 STTransform3::multiply(STPoint3 point){
	STVector3 colVector(point);
	STVector3 result;
	result.x = STVector3::Dot(STVector3(_M[0][0],_M[0][1],_M[0][2]), colVector);
	result.y = STVector3::Dot(STVector3(_M[1][0],_M[1][1],_M[1][2]), colVector);
	result.z = STVector3::Dot(STVector3(_M[2][0],_M[2][1],_M[2][2]), colVector);
	return STPoint3(result);
}

STTransform3 STTransform3::multiply(const STTransform3 left, const STTransform3 right){
	float prod[3][3]; 
	for(int i = 0; i < 3; i++){
		const float *row = left._M[i];
		STVector3 rowVector(row[0], row[1], row[2]);
		prod[i][0] = STVector3::Dot(rowVector, STVector3(right._M[0][0], right._M[1][0], right._M[2][0]));
		prod[i][1] = STVector3::Dot(rowVector, STVector3(right._M[0][1], right._M[1][1], right._M[2][1]));
		prod[i][2] = STVector3::Dot(rowVector, STVector3(right._M[0][2], right._M[1][2], right._M[2][2]));
	}
	return STTransform3(prod);
}