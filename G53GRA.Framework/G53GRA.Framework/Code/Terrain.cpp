#include "Terrain.h"
#include <iostream>
#include <fstream>
#include <assert.h>
Terrain::Terrain(int width, int depth, const std::string& filename)
	:width(width), depth(depth), size(width* (depth - 1) * 2)
{
	texID = Scene::GetTexture(filename);
	vertices = createVertices();
	indices = createIndices();
	alterTerrain(vertices, "./Textures/heightMap.bmp");
	colours = colorPoint();
	normals = createNormals();
	textureCoords = textureCoordinate();
}

void Terrain::alterTerrain(Vertex** vertices, const std::string& heightMap) {
	std::ifstream file(heightMap, std::ios::binary);
	BITMAPFILEHEADER bmpHeader;
	file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
	BITMAPINFOHEADER bmpInfoHeader;
	file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
	assert(bmpInfoHeader.biBitCount == 24);
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
			vertices[i++]->position[1] = (float)vertexHeight / 255;
		}
		file.seekg(padding, std::ios::cur);
	}
}

GLfloat* Terrain::colorPoint() {
	GLfloat* colorPoint = new GLfloat[width * depth * 3];
	int j = 0;
	for (int i = 0; i < width * depth; i++) {
		float vertexHeight = vertices[i]->position[1];
		if (vertexHeight <= 0.60) {
			colorPoint[j++] = (float)89 / 255;
			colorPoint[j++] = (float)68 / 255;
			colorPoint[j++] = (float)48 / 255;
		}
		else if (vertexHeight <= 0.64) {
			colorPoint[j++] = (float)89 / 255;
			colorPoint[j++] = (float)68 / 255;
			colorPoint[j++] = (float)48 / 255;
		}
		else if (vertexHeight <= 0.69) {
			colorPoint[j++] = (float)98 / 255;
			colorPoint[j++] = (float)77 / 255;
			colorPoint[j++] = (float)62 / 255;
		}
		else if (vertexHeight <= 0.74) {
			colorPoint[j++] = (float)126 / 255;
			colorPoint[j++] = (float)101 / 255;
			colorPoint[j++] = (float)88 / 255;
		}
		else if (vertexHeight <= 0.78) {
			colorPoint[j++] = (float)130 / 255;
			colorPoint[j++] = (float)100 / 255;
			colorPoint[j++] = (float)81 / 255;
		}
		else if (vertexHeight <= 0.80) {
			colorPoint[j++] = (float)135 / 255;
			colorPoint[j++] = (float)100 / 255;
			colorPoint[j++] = (float)90 / 255;
		}
		else if (vertexHeight <= 0.85) {
			colorPoint[j++] = (float)129 / 255;
			colorPoint[j++] = (float)108 / 255;
			colorPoint[j++] = (float)83 / 255;
		}
		else if (vertexHeight <= 0.89) {
			colorPoint[j++] = (float)133 / 255;
			colorPoint[j++] = (float)112 / 255;
			colorPoint[j++] = (float)91 / 255;
		}
		else {
			colorPoint[j++] = (float)131 / 255;
			colorPoint[j++] = (float)109 / 255;
			colorPoint[j++] = (float)89 / 255;
		}
	}
	return colorPoint;
}

GLint** Terrain::createIndices() {
	GLint** indices = new GLint*[depth - 1];
	int i = 0;
	int j = 0;
	for (int column = 0; column < depth - 1; column++) {
		GLint* entry = new GLint[width * 2];
		for (int row = 0; row < width; row++) {
			entry[i++] = row + (column * depth);
			entry[i++] = row + ((column + 1) * depth);
		}
		for (int k = 0; k < width * 2; k++) {
		}
		i = 0;
		indices[j++] = entry;
		std::cout << std::endl;
	}
	return indices;
}
GLfloat* Terrain::normalise(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	GLfloat normal[3] = {
		x / length,
		y / length,
		z / length
	};
	return normal;
}

GLfloat** Terrain::createNormals()
{
	GLfloat** norms = new GLfloat*[width * depth * 3];
	int i = 0;
	for (int row = 0; row < width; row++) {
		for (int column = 0; column < depth; column++) {
			int numNeighbours = 0;
			int index = column + (row * depth);
			Vertex* current = vertices[index];
			Vertex* up = vertices[(column)+((row + 1) * depth)];
			Vertex* right = vertices[(column + 1) + (row * depth)];
			Vertex* downRight = vertices[(column + 1) + ((row - 1) * depth)];
			Vertex* down = vertices[column + ((row - 1) * depth)];
			Vertex* left = vertices[(column - 1) + (row * depth)];
			Vertex* leftUp = vertices[(column - 1) + ((row + 1) * depth)];
			GLfloat* N1 = new GLfloat[3];
			GLfloat* N2 = new GLfloat[3];
			GLfloat* N3 = new GLfloat[3];
			GLfloat* N4 = new GLfloat[3];
			GLfloat* N5 = new GLfloat[3];
			GLfloat* N6 = new GLfloat[3];
			GLfloat* N = new GLfloat[3];
			if (column == 0) {
				if (row == 0) {
					N = right->crossProduct(up->position);
					N = normalise(N[0],N[1],N[2]);
				}
				else if (row == (depth - 1)) {
					N1 = down->crossProduct(downRight->position);
					N2 = downRight->crossProduct(right->position);
					N[0] = N1[0] + N2[0];
					N[1] = N1[1] + N2[1];
					N[2] = N1[2] + N2[2];
					N = normalise(N[0], N[1], N[2]);
				}
				else {
					N1 = down->crossProduct(downRight->position);
					N2 = downRight->crossProduct(right->position);
					N3 = right->crossProduct(up->position);
					N[0] = N1[0] + N2[0] + N3[0];
					N[1] = N1[1] + N2[1] + N3[1];
					N[2] = N1[2] + N2[2] + N3[2];
					N = normalise(N[0], N[1], N[2]);
				}
			}
			else if (column == (width - 1)) {
				if (row == 0) {
					N1 = up->crossProduct(leftUp->position);
					N2 = leftUp->crossProduct(left->position);
					N[0] = N1[0] + N2[0];
					N[1] = N1[1] + N2[1];
					N[2] = N1[2] + N2[2];
					N = normalise(N[0], N[1], N[2]);
				}
				else if (row == (depth - 1)) {
					N = left->crossProduct(down->position);
					N = normalise(N[0], N[1], N[2]);
				}
				else {
					N1 = up->crossProduct(leftUp->position);
					N2 = leftUp->crossProduct(left->position);
					N3 = left->crossProduct(down->position);
					N[0] = N1[0] + N2[0] + N3[0];
					N[1] = N1[1] + N2[1] + N3[1];
					N[2] = N1[2] + N2[2] + N3[2];
					N = normalise(N[0], N[1], N[2]);
				}
			}
			else if (row == 0) {
				N1 = up->crossProduct(leftUp->position);
				N2 = leftUp->crossProduct(left->position);
				N3 = right->crossProduct(up->position);
				N[0] = N1[0] + N2[0] + N3[0];
				N[1] = N1[1] + N2[1] + N3[1];
				N[2] = N1[2] + N2[2] + N3[2];
				N = normalise(N[0], N[1], N[2]);
			}
			else if (row == (depth - 1)) {
				N1 = left->crossProduct(down->position);
				N2 = down->crossProduct(downRight->position);
				N3 = downRight->crossProduct(right->position);
				N[0] = N1[0] + N2[0] + N3[0];
				N[1] = N1[1] + N2[1] + N3[1];
				N[2] = N1[2] + N2[2] + N3[2];
				N = normalise(N[0], N[1], N[2]);
			}
			else {
				N1 = up->crossProduct(leftUp->position);
				N2 = leftUp->crossProduct(left->position);
				N3 = left->crossProduct(down->position);
				N4 = down->crossProduct(downRight->position);
				N5 = downRight->crossProduct(right->position);
				N6 = right->crossProduct(up->position);

				N[0] = N1[0] + N2[0] + N3[0] + N4[0] + N5[0] + N6[0];
				N[1] = N1[1] + N2[1] + N3[1] + N4[1] + N5[1] + N6[1];
				N[2] = N1[2] + N2[2] + N3[2] + N4[2] + N5[2] + N6[2];
				N = normalise(N[0], N[1], N[2]);
			}
			norms[i] = N;
		}
	}
	return norms;
}

GLfloat* Terrain::textureCoordinate() {
	GLfloat* texCoords = new GLfloat[width * depth * 8];
	int j = 0;
	for (int i = 0; i < width * depth; i++) {
		if (i % 2 == 0) {
			texCoords[j++] = 0;
			texCoords[j++] = 0;

			texCoords[j++] = 0;
			texCoords[j++] = 1;

			texCoords[j++] = 1;
			texCoords[j++] = 0;
		}
		else {
			texCoords[j++] = 0;
			texCoords[j++] = 1;

			texCoords[j++] = 1;
			texCoords[j++] = 0;

			texCoords[j++] = 1;
			texCoords[j++] = 1;	
			
			texCoords[j++] = 0;	
			texCoords[j++] = 0;	
			
			texCoords[j++] = 1;
			texCoords[j++] = 1;
		}
	}
	return texCoords;
}

Vertex** Terrain::createVertices() {
	Vertex** vertices = new Vertex * [width * depth];
	int i = 0;
	for (int row = 0; row < width; row++) {
		for (int column = 0; column < depth; column++) {
			Vertex* vertex = new Vertex((float)column, 0.f, (float)row);
			vertex->defined = true;
			vertices[i++] = vertex;
		}
	}
	return vertices;
}

void Terrain::Display() {
	glPushMatrix();
	glTranslatef(-1000.f, -800, -1000.f);
	glScalef(2000.f / (width - 1), 1000.f, 2000.f / (depth - 1));
	DrawTerrain();
	glPopMatrix();
}

void Terrain::DrawTerrain() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnableClientState(GL_COLOR_ARRAY);
	GLfloat* secretSauce = new GLfloat[width * depth * 3];
	int i = 0;
	for (int j = 0; j < width * depth; j++) {
		secretSauce[i++] = vertices[j]->position[0];
		secretSauce[i++] = vertices[j]->position[1];
		secretSauce[i++] = vertices[j]->position[2];
	}
	glNormalPointer(GL_FLOAT, 0, normals);
	glVertexPointer(3, GL_FLOAT, 0, secretSauce);
	glColorPointer(3, GL_FLOAT, 0, colours);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
	
	for (int j = 0; j < depth - 1; j++) {
		glDrawElements(GL_TRIANGLE_STRIP, width * 2, GL_UNSIGNED_INT, indices[j]);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	delete []secretSauce;
}