#pragma once

#include "DisplayableObject.h"
#include <vector>
#include <Vertex.h>
class Terrain:
	public DisplayableObject
{
public:
	Terrain(int width, int depth, const std::string& filename);
	~Terrain() {};
	void alterTerrain(Vertex** , const std::string& heightMap);
	GLfloat* colorPoint();
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
	GLint texID;
private:
	void DrawTerrain();
};


