#pragma once
#include <cstdio>

class Vertex
{
public:
	Vertex(float x, float y, float z);
	bool isEmpty();
	~Vertex() {};
	float position[3];
	float color[3];
	float texcoord[3];
	float* crossProduct(float* vector);
	float* add(float* vector);
	float* sub(float* vector);
	float normal[3];
	bool defined;
private:

};