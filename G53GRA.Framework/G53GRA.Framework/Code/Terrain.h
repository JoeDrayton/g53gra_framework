#pragma once

#include "DisplayableObject.h"
#include <vector>
class Terrain:
	public DisplayableObject
{
public:
	Terrain(int width, int depth, const std::string& filename);
	~Terrain() {};
	GLfloat* generateVertices();
	GLint* generateIndices();
	void Display();
	int width;
	int depth;
	GLint* indices;
	GLfloat* vertices;
	const int size;
private:
	GLint texID;
	void DrawTerrain();
};


