#include "Terrain.h"

Terrain::Terrain(int width, int depth, const std::string& filename)
:width(width),depth(depth),size(width* (depth - 1) * 2)
{
	texID = Scene::GetTexture(filename);
	vertices = generateVertices();
	indices = generateIndices();


}

GLfloat* Terrain::generateVertices() { 
	GLfloat* vertices = new GLfloat[width * depth * 3];
	int i = 0;
	for (int row = 0; row < width; row++) {
		for (int column = 0; column < depth; column++) {
			vertices[i++] = (float) column;
			vertices[i++] = 0.f;
			vertices[i++] = (float)row;
		}
	}
	return vertices;
}


GLint* Terrain::generateIndices() {
	GLint* indices = new GLint[size];
	int i = 0;
	for (int column = 0; column < depth - 1; column++) {
		for (int row = 0; row < width; row++) {
			indices[i++] = row + (column * depth);
			indices[i++] = row + ((column + 1) * depth);
		}
	}
	return indices;
}

void Terrain::Display() {
	glPushMatrix();
	glTranslatef(-1000.f, -10.f, -1000.f);
	glScalef(2000.f / width, 1000.f, 2000.f/depth);
	DrawTerrain();
	glPopMatrix();
}



void Terrain::DrawTerrain() {
	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	glColor3f(0.5f, 0.3f, 0.18f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, indices);
	glColor3f(0.5f, 0.2f, 0.3f);
	glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);


	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

