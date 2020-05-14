#pragma once
#define _USE_MATH_DEFINES

#include "DisplayableObject.h"
#include "Animation.h"
#include "Vertex.h"
#include <cmath>

class Cylinder :
	public DisplayableObject,
	public Animation
{
public:
	Cylinder(
		GLfloat radius, GLfloat height, GLfloat rotateX,
		GLfloat rotateY, GLfloat rotateZ, GLfloat X, GLfloat Y, GLfloat Z, GLubyte R, GLubyte G, GLubyte B,
		bool stripey);
	~Cylinder() {};
	void setRotateZ(GLfloat z);
	void drawCylinder();
	void Display();
	void Update(const double& deltaTime);
private:
	int sectorCount;
	GLfloat rotateX, rotateY, rotateZ, X, Y, Z, height, radius;
	GLubyte R, G, B;
	bool stripey;
};

