#pragma once
#include "Terrain.h"
#include "Animation.h"
#include <iostream>
class RainbowTerrain :
	public Terrain,
	public DisplayableObject,
	public Animation
{
public:
	RainbowTerrain(int width, int depth);
	void colourShift();
	GLfloat* colorPoint();
	void Update(const double& deltaTime);
	void Display();
	void DrawTerrain();
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
	int theta;
};

