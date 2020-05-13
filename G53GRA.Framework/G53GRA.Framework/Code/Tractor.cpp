#include "Tractor.h"

GLfloat* generateColours(GLfloat R, GLfloat G, GLfloat B) {
	GLfloat* colours = new GLfloat[36];
	for (int i = 0; i < 36; i += 3) {
		int random = std::rand() % 20;
		colours[i] = (GLfloat)R/256;
		colours[i+1] = (GLfloat)G/256;
		colours[i+2] = (GLfloat)B/256;
	}
	return colours;
}

void Tractor::DrawTractor() {
	DrawCube(
		0, 0, 4,
		30, 0, 4,
		30, 15, 4,
		0, 15, 4,
		0, 0, 12,
		30, 0, 12,
		30, 15, 12,
		0, 15, 12,
		163, 3, 3);	

	DrawCube(
		45, 0, 2,
		30, 0, 2,
		30, 15, 2,
		45, 15, 2,
		45, 0, 15,
		30, 0, 15,
		30, 15, 15,
		45, 15, 15,
		163, 3, 3);

	Cylinder* cylinder5 = new Cylinder(1.0, 14.0, 0, 0, 0, 5, -2.5, 1, 40, 3, 3);
	Cylinder* cylinder6 = new Cylinder(1.0, 15.0, 0, 0, 0, 40, 0, 1, 40, 3, 3);

	Cylinder* front1 = new Cylinder(5.0, 3.0, 0, 0, 0, 5, -2.5, 0, 20, 20, 20);
	Cylinder* front2 = new Cylinder(5.0, 3.0, 0, 0, 0, 5, -2.5, 13, 20,20,20);
	Cylinder* back1 = new Cylinder(8.0, 4, 0, 0, 0, 40, 0, -2, 20, 20, 20);
	Cylinder* back2 = new Cylinder(8.0, 4, 0, 0, 0, 40, 0, 15, 20, 20, 20);
}

void Tractor::Display() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-50, -20, -200);
	glScalef(10.0, 10.0, 10.0);
	DrawTractor();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Tractor::DrawCube(
	GLfloat A0, GLfloat A1, GLfloat A2, 
	GLfloat B0, GLfloat B1, GLfloat B2,
	GLfloat C0, GLfloat C1, GLfloat C2,
	GLfloat D0, GLfloat D1, GLfloat D2,
	GLfloat E0, GLfloat E1, GLfloat E2,
	GLfloat F0, GLfloat F1, GLfloat F2,
	GLfloat G0, GLfloat G1, GLfloat G2,
	GLfloat H0, GLfloat H1, GLfloat H2,
	GLint R, GLint G, GLint B) {


	GLfloat* vertices = new GLfloat[24]{
		A0, A1, A2, //A
		B0, B1, B2, //B
		C0, C1, C2, //C
		D0, D1, D2, //D
		E0, E1, E2, //E
		F0, F1, F2, //F
		G0, G1, G2, //G
		H0, H1, H2 //H
	};

	GLint sideNormals[30]{
		0,0,1, // front
		0,0,1, // front
		1,0,0, // right
		1,0,0, // right
		0,0,-1, // back
		0,0,-1, // back
		-1,0,0, //left
		-1,0,0, //left
	};

	GLint topNormals[6]{
		0,1,0,
		0,1,0
	};
	
	GLint bottomNormals[6]{
		0,-1,0,
		0,-1,0
	};

	GLint sides[10]{
		0,3,1,2,5,6,4,7,0,3
	};

	GLint bottom[4]{
		0,4,1,5
	};

	GLint top[4]{
		3,7,2,6
	};

	GLfloat color[60]{
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875,
		0.63671875, 0.01171875, 0.01171875
		
	};
	for (int i = 0; i < 8; i++) {

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glNormalPointer(GL_FLOAT, 0, sideNormals);
		glColorPointer(3, GL_FLOAT, 0, generateColours(R,G,B));
		glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, sides);
		glNormalPointer(GL_FLOAT, 0, topNormals);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, top);
		glDisable(GL_CULL_FACE);
		glNormalPointer(GL_FLOAT, 0, bottomNormals);
		glEnable(GL_CULL_FACE);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, bottom);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	delete[] vertices;
}