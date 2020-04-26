#pragma once

#include "../Framework/Engine/Scene.h"
#include "Skybox.h"
#include "TestObject.h"
#include "Terrain.h"
#include "Vertex.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:
	void Initialise();
	void Projection();

};