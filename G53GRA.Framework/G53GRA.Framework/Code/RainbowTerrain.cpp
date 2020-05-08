#include "RainbowTerrain.h"
#include <cmath>

RainbowTerrain::RainbowTerrain(int width, int depth, const std::string& filename)
: Terrain::Terrain(width, depth, filename), width(width), depth(depth), size(width* (depth - 1) * 2)
{
	std::cout << "Victory we have victory" << std::endl;
	vertices = createVertices();
	indices = createIndices();
	//alterTerrain(vertices, "./Textures/heightMap.bmp");
	colours = colorPoint();
	theta = 0;
}

void RainbowTerrain::colourShift() {
	GLfloat tempColour1 = colours[(width * depth * 3)-1];
	GLfloat tempColour2 = colours[(width * depth * 3)-2];
	GLfloat tempColour3 = colours[(width * depth * 3)-3];
	GLfloat front1, front2, front3;
	for (int i = 0; i < width * depth * 3; i += 3) {
		front1 = colours[i];
		front2 = colours[i + 1];
		front3 = colours[i + 2];
		colours[i] = tempColour1;
		colours[i + 1] = tempColour2;
		colours[i + 2] = tempColour3;
		tempColour1 = front1;
		tempColour2 = front2;
		tempColour3 = front3;
	}
	std::cout << std::endl;
}

GLfloat* RainbowTerrain::colorPoint() {
	GLfloat* colorPoint = new GLfloat[width * depth * 3];
	int i = 0;
	for (int col = 0; col < width; col++) {
		for (int row = 0; row < depth; row++) {
			float random = (float)std::rand() / (float)RAND_MAX;
			colorPoint[i++] = random;
			random = (float)std::rand() / (float)RAND_MAX;
			colorPoint[i++] = random;
			random = (float)std::rand() / (float)RAND_MAX;
			colorPoint[i++] = random;
		}
	}
	return colorPoint;
}

void RainbowTerrain::Update(const double& deltaTime)
{	
	if (theta % 26 == 0) {
	//if (fmod(deltaTime, 0.007) < 0.005) {
		for (int i = 0; i < width * depth; i++) {
				vertices[i]->position[0] += 1 * cos(theta);
				vertices[i]->position[1] += 0.005 * sin(theta);
				vertices[i]->position[2] += 1 * cos(theta);
				theta++;
		}
	}
	else {
		if (theta == 360) {
			theta = 0;
		}
		else {
			theta++;
		}
	}
	
}

void RainbowTerrain::Display() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-1000.f, -130, -1000.f);
	glScalef(2000.f / (width - 1), 1000.f, 2000.f / (depth - 1));
	RainbowTerrain::DrawTerrain();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RainbowTerrain::DrawTerrain() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	GLfloat* secretSauce = new GLfloat[width * depth * 3];
	int i = 0;
	for (int j = 0; j < width * depth; j++) {
		secretSauce[i++] = vertices[j]->position[0];
		secretSauce[i++] = vertices[j]->position[1];
		secretSauce[i++] = vertices[j]->position[2];
	}
	glVertexPointer(3, GL_FLOAT, 0, secretSauce);
	glColorPointer(3, GL_FLOAT, 0, colours);
	for (int j = 0; j < depth - 1; j++) {
		glDrawElements(GL_TRIANGLE_STRIP, width * 2, GL_UNSIGNED_INT, indices[j]);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	delete[]secretSauce;
}