#pragma once
#include "DisplayableObject.h"
#include "Cylinder.h"
class Tractor :
	public DisplayableObject
{
	void DrawTractor();
	void Display();
	void DrawCube(
		GLfloat A0, GLfloat A1, GLfloat A2,
		GLfloat B0, GLfloat B1, GLfloat B2,
		GLfloat C0, GLfloat C1, GLfloat C2,
		GLfloat D0, GLfloat D1, GLfloat D2,
		GLfloat E0, GLfloat E1, GLfloat E2,
		GLfloat F0, GLfloat F1, GLfloat F2,
		GLfloat G0, GLfloat G1, GLfloat G2,
		GLfloat H0, GLfloat H1, GLfloat H2,
		GLint R, GLint G, GLint B);
};

