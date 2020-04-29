#pragma once

class Vertex
{
public:
	Vertex(float x, float y, float z);
	~Vertex() {};
	float position[3];
	float color[3];
	float texcoord[3];
	float normal[3];
private:

};