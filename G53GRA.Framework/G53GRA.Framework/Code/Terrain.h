#pragma once

#include "DisplayableObject.h"
#include <vector>
#include <Vertex.h>
class Terrain:
	public DisplayableObject
{
public:
	Terrain(int width, int depth, const std::string& filename);
	void alterTerrain(const std::string& heightMap);
	GLfloat* colorPoint();
	~Terrain() {};
	GLint** createIndices();
	GLfloat* normalise(GLfloat x, GLfloat y, GLfloat z);
	GLfloat** createNormals();
	GLfloat* textureCoordinate();
	Vertex** createVertices();
	void Display();
	const int width;
	const int depth;
	GLint** indices;
	Vertex** vertices;
	GLfloat** normals;
	GLfloat* colours;
	GLfloat* textureCoords;
	const int size;
	char* heightMap;
private:
	GLint texID;
	void DrawTerrain();
};


