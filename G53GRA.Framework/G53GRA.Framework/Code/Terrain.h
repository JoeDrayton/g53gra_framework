#pragma once

#include "DisplayableObject.h"
#include <vector>
#include <Vertex.h>
class Terrain:
	public DisplayableObject
{
public:
	Terrain(int width, int depth, const std::string& filename);
	void alterTerrain(float min, float max, float rate, const std::string& heightMap);
	GLfloat* colorPoint();
	~Terrain() {};
	GLfloat* generateVertices();
	GLint* generateIndices();
	Vertex** createVertices();
	void Display();
	int width;
	int depth;
	GLint* indices;
	Vertex** vertices;
	GLfloat* colours;
	const int size;
	char* heightMap;
private:
	GLint texID;
	void DrawTerrain();
};


