#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Cylinder.h"
class Tractor :
	public DisplayableObject,
	public Animation
{
public:
	Tractor(GLfloat X, GLfloat Y, GLfloat Z);
	void resetRotation();
	~Tractor() {};
	void DrawTractor();
	void Display();
	void Update(const double& deltaTime);
	void DrawCube(GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xLength, GLfloat yLength, GLfloat zLength, GLfloat R, GLfloat G, GLfloat B);
	bool goTime;
private:
	Cylinder* axel1;
	Cylinder* axel2;
	Cylinder* front1;
	Cylinder* front2; 
	Cylinder* back1;
	Cylinder* back2;
	Cylinder* frontTrim1;
	Cylinder* frontTrim2; 
	Cylinder* backTrim1;
	Cylinder* backTrim2;
	Cylinder* wheel;
	Cylinder* wheelShaft;
	Cylinder* spout1;
	Cylinder* spout2;
	GLfloat wheelRotate, X, Y, Z, rotateX, rotateY, rotateZ;
};

