#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, GLfloat height, GLfloat rotateX,
	GLfloat rotateY, GLfloat rotateZ, GLfloat X, GLfloat Y, GLfloat Z, GLubyte R, GLubyte G, GLubyte B)
	:radius(radius), height(height), 
	rotateX(rotateX), rotateY(rotateY), rotateZ(rotateZ),
	X(X), Y(Y), Z(Z), R(R), G(G), B(B)
{
	Display();
}


void Cylinder::drawCylinder()
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glColor3f(R - 40, G - 40, B - 40);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * M_PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		glNormal3f(x, y, height);
		glNormal3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glNormal3f(radius, 0.0, height);
	glNormal3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glColor3ub(R, G, B);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * M_PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glNormal3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glNormal3f(radius, 0, height);
	glEnd();

	/** Draw the circle on bottom of cylinder */
	glRotatef(180.f, 0, 1, 0);
	glColor3ub(R, G, B);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * M_PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, 0.0);
		glNormal3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, 0.0);
	glNormal3f(radius, 0, 0);
	glEnd();
}



void Cylinder::Display()
{
	glPushMatrix();
	glTranslatef(X, Y, Z);
	glRotatef(rotateX, 1.f, 0.f, 0.f);
	glRotatef(rotateY, 0.f, 1.f, 0.f);
	glRotatef(rotateZ, 0.f, 0.f, 1.f);
	glScalef(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	drawCylinder();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}
