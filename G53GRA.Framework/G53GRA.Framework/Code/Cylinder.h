#pragma once
#define _USE_MATH_DEFINES

#include "DisplayableObject.h"
#include "Vertex.h"
#include <cmath>

class Cylinder :
	public DisplayableObject

{
public:
	Cylinder(
		GLfloat radius, GLfloat height, GLfloat rotateX,
		GLfloat rotateY, GLfloat rotateZ, GLfloat X, GLfloat Y, GLfloat Z, GLubyte R, GLubyte G, GLubyte B);
	~Cylinder() {};
	void drawCylinder();
	void Display();
private:
	int sectorCount;
	GLfloat rotateX, rotateY, rotateZ, X, Y, Z, height, radius;
	GLubyte R, G, B;
};

