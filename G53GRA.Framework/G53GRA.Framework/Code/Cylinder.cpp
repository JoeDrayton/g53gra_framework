#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, GLfloat height, GLfloat rotateX,
	GLfloat rotateY, GLfloat rotateZ, GLfloat X, GLfloat Y, GLfloat Z, GLubyte R, GLubyte G, GLubyte B, bool stripey)
	:radius(radius), height(height), 
	rotateX(rotateX), rotateY(rotateY), rotateZ(rotateZ),
	X(X), Y(Y), Z(Z), R(R), G(G), B(B), stripey(stripey)
{

}


void Cylinder::setRotateZ(GLfloat z) {
	rotateZ = z;
}

void Cylinder::drawCylinder()
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1f;
	/** Draw the tube */
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	int i = 0;
	while (angle < 2 * M_PI) {
		float result = fmodf(angle, 0.1);
		if (stripey) {
			if (i++ % 3 < 2) {
				glColor3ub(R - 20, G - 20, B - 20);

			}
			else {
				glColor3ub(R, G, B);
			}
		}
		else {
			glColor3ub(R - 10, G - 10, B - 10);
		}
		
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

float mat_colour[]                      // colour reflected by diffuse light
= { 0.513f, 0.4274f, 0.34901f, 1.f };         // mid brown
float mat_ambient[]                     // ambient colour
= { 0.34901f, 0.26666f, 0.18823f };         // dark brown
float mat_spec[]                        // specular colour
= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)


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
	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance
	drawCylinder();
	glPopAttrib();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}

void Cylinder::Update(const double& deltaTime)
{
}
