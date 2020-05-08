#pragma once

#include "../Framework/Engine/Scene.h"
#include "Skybox.h"
#include "Terrain.h"
#include "RainbowTerrain.h"
#include "Door.h"
#include "Eye.h"
#include <iostream>
class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};
	Camera* camera;
	Skybox* sb;
	GLuint* skybox;
	GLuint* spacebox;
	GLuint* eyeTextures;
	Eye* eye[5];
	Terrain* terrain;
	RainbowTerrain* rt;
	Door* door;
private:
	bool spaceMode;
	void Initialise();
	void Update(const double& deltaTime);
	void Projection();

};