#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	defined = false;
}

float* Vertex::crossProduct(float* vector) {
	float cross[3];
	cross[0] = position[1] * vector[2] - position[2] * vector[1];
	cross[1] = position[2] * vector[0] - position[0] * vector[2];
	cross[2] = position[0] * vector[1] - position[1] * vector[0];
	return cross;
}

float* Vertex::add(float* vector) {
	float add[3];
	add[0] = position[0] + vector[0];
	add[1] = position[1] + vector[1];
	add[2] = position[2] + vector[2];
	return add;
}

float* Vertex::sub(float* vector) {
	float sub[3];
	sub[0] = position[0] - vector[0];
	sub[1] = position[1] - vector[1];
	sub[2] = position[2] - vector[2];
	return sub;
}