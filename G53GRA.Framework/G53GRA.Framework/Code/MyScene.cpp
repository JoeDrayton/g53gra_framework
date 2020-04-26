#include "MyScene.h"
#include "TexturedQuad.h"
MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	
	//Light 0
	GLfloat ambience[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	//Light 1
	float red[] = { 0.5f, 0.5f, 0.5f, 1 };
	float reda[] = { 0.1f, 0, 0, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, reda);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT1, GL_SPECULAR, red);

	float gr[] = { 0, 0.5f, 0, 1 };
	float gra[] = { 0, 0.1f, 0, 1 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, gra);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, gr);
	glLightfv(GL_LIGHT2, GL_SPECULAR, gr);

	float bl[] = { 0, 0, 0.5f, 1 };
	float bla[] = { 0, 0, 0.1f, 1 };
	glLightfv(GL_LIGHT3, GL_AMBIENT, bla);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, bl);
	glLightfv(GL_LIGHT3, GL_SPECULAR, bl);

	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);
	

	// uncomment one of TestObje to see the sample
	//These samples are provided just to give you some idea in how openGL function works, the code is not very well written for use in a large project

	//Sample 1: basic translate, rotate and scale
	//TestObj1* obj = new TestObj1();

	//Hierarchical model with animation
	//TestObj2* obj = new TestObj2();

	//Cubes for different projection view, change code below in MyScene::Projection()
	//TestObj3* obj = new TestObj3();

	// Sample of a simple fps game, learn ways to control camera, check code in camera.cpp
	TestObject* obj = new TestObject();
	//TBA
	//TestObj5* obj = new TestObj5();

	Skybox* sb = new Skybox();
	GLuint* skybox = new GLuint[5];
	skybox[0] = Scene::GetTexture("./Textures/skybox-left.bmp");
	skybox[1] = Scene::GetTexture("./Textures/skybox-right.bmp");
	skybox[2] = Scene::GetTexture("./Textures/skybox-front.bmp");
	skybox[3] = Scene::GetTexture("./Textures/skybox-back.bmp");
	skybox[4] = Scene::GetTexture("./Textures/skybox-top.bmp");

	Terrain* terrain = new Terrain(1000, 1000, "./Textures/groundTexture.bmp");

	sb->setTextures(skybox);
	AddObjectToScene(sb);
	AddObjectToScene(terrain);
	//AddObjectToScene(obj);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 10000.0);
}
