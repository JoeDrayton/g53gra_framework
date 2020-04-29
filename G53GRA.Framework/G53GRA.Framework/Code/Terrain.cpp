#include "Terrain.h"
#include <iostream>
#include <fstream>
#include <assert.h>
Terrain::Terrain(int width, int depth, const std::string& filename)
:width(width),depth(depth),size(width* (depth - 1) * 2)
{
	texID = Scene::GetTexture(filename);
	vertices = createVertices();
	indices = generateIndices();
	colours = colorPoint();
	alterTerrain(0, 0, 0, "./Textures/heightMap.bmp");
}

void Terrain::alterTerrain(float min, float max, float rate, const std::string& heightMap) {
	std::ifstream file(heightMap, std::ios::binary);
	BITMAPFILEHEADER bmpHeader;
	file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
	printf("I hate it all \n");

	BITMAPINFOHEADER bmpInfoHeader;
	file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
	assert(bmpInfoHeader.biBitCount == 24);
	//assert(bmpInfoHeader.biCompression = BI_RGB);

	int w = bmpInfoHeader.biWidth;
	int h = bmpInfoHeader.biHeight;

	file.seekg(bmpHeader.bfOffBits);

	const int padding = (4 - (w * 3) % 4) % 4;
	int vertexHeight;
	int i = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			vertexHeight = file.get();
			file.get();
			file.get();
			vertices[i++]->position[1] = (float)vertexHeight/150;
		}
		file.seekg(padding, std::ios::cur);
	}
}

GLfloat* Terrain::colorPoint(){
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

Vertex** Terrain::createVertices() {
	Vertex** vertices = new Vertex*[width * depth];
	int i = 0;
	for (int row = 0; row < width; row++) {
		for (int column = 0; column < depth; column++) {
			Vertex* vertex = new Vertex((float)column, 0.f, (float)row);
			vertices[i++] = vertex;
		}
	}/*
	for (i = 0; i < width* depth; i++) {
		std::cout << "Bullshit: " << vertices[i]->position[0] << ", " << vertices[i]->position[1] << ", " << vertices[i]->position[2] << std::endl;
	}
	 */
	return vertices;
}

void Terrain::Display() {
	glPushMatrix();
	glTranslatef(-1000.f, -1550.f, -1000.f);
	glScalef(2000.f / (width - 1), 1000.f, 2000.f/(depth - 1));
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


	//glColor3f(0.5f, 0.3f, 0.18f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	GLfloat* secretSauce = new GLfloat[width * depth * 3];
	int i = 0;
	for (int j = 0; j < width * depth; j++) {
			secretSauce[i++] = vertices[j]->position[0];
			secretSauce[i++] = vertices[j]->position[1];
			secretSauce[i++] = vertices[j]->position[2];
	}
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glVertexPointer(3, GL_FLOAT, 0, secretSauce);
	glColorPointer(3, GL_FLOAT, 0, colours);
	glColor3f(0.5f, 0.2f, 0.3f);
	glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, indices);
	//glDrawArrays(GL_TRIANGLE_STRIP, indices[0], size);
	glDisableClientState(GL_VERTEX_ARRAY);
	delete secretSauce;

	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

