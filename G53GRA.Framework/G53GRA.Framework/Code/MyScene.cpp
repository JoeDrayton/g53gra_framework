#include "MyScene.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight), spaceMode(false)
{

}
//Light 0
GLfloat ambience[] = { 1.f, 1.f, 1.f, 1.0f };
GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { -25, 100.f, -25.f, 0.f };
//Light 1
float ambient1[] = { 1.f, 0.f, 0.f, 1.f };
float diffuse1[] = { 0.f, 0.f, 0.f, 1.f };
float position1[] = { -15.f, 200.0f, 125, 1.0f };
//Light 2
float ambient2[] = { 0.f, 0.f, 1.f, 1.f };
float diffuse2[] = { 0.f, 0.f, 0.f, 1.f };
float position2[] = { 15.f, 200.0f, 125.f, 1.0f };
//Light 3
GLfloat ambience3[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuse3[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat specular3[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float position3[] = { -25.f, 100.0f, -25.f, 0.0f };

float spot_direction[] = { 0.f, -1.f, -1.f };

void MyScene::Initialise()
{
	glClearColor(0.1f, 0.0f, 0.0f, 1.0f);	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.9);

	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.f);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 70.f);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.9);

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 30.f);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 70.f);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambience3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);
	glLightfv(GL_LIGHT3, GL_POSITION, position3);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	camera = this->GetCamera();
	sb = new Skybox();
	skybox = new GLuint[5];
	spacebox = new GLuint[5];
	eyeTextures = new GLuint[5];
	terrain = new Terrain(100, 100, "./Textures/ground-texture.bmp");
	rt = new RainbowTerrain(100, 100, "./Textures/rainbow-texture");
	door = new Door("./Textures/door-front.bmp", "./Textures/door-back.bmp", "./Textures/door-side.bmp","./Textures/portal.bmp", camera);
	skybox[0] = Scene::GetTexture("./Textures/skybox-left.bmp");
	skybox[1] = Scene::GetTexture("./Textures/skybox-right.bmp");
	skybox[2] = Scene::GetTexture("./Textures/skybox-front.bmp");
	skybox[3] = Scene::GetTexture("./Textures/skybox-back.bmp");
	skybox[4] = Scene::GetTexture("./Textures/skybox-top.bmp");
	spacebox[0] = Scene::GetTexture("./Textures/spacebox-left.bmp");
	spacebox[1] = Scene::GetTexture("./Textures/spacebox-right.bmp");
	spacebox[2] = Scene::GetTexture("./Textures/spacebox-front.bmp");
	spacebox[3] = Scene::GetTexture("./Textures/spacebox-back.bmp");
	spacebox[4] = Scene::GetTexture("./Textures/spacebox-top.bmp");
	eyeTextures[0] = Scene::GetTexture("./Textures/Eye1.bmp");
	eyeTextures[1] = Scene::GetTexture("./Textures/Eye2.bmp");
	eyeTextures[2] = Scene::GetTexture("./Textures/Eye3.bmp");
	eyeTextures[3] = Scene::GetTexture("./Textures/Eye4.bmp");
	eyeTextures[4] = Scene::GetTexture("./Textures/Eye5.bmp");
	sb->setTextures(skybox);
	AddObjectToScene(sb);
	AddObjectToScene(door);
	AddObjectToScene(terrain);
	eye[0] = new Eye(camera, 0.f, 40, 0.f, 0.f, -50.f, 100.f, -900.f);
	eye[1] = new Eye(camera, 90.f, 0.f, 0.f, -49.f, -800.f, 100.f, 100.f);
	eye[2] = new Eye(camera, 180.f, -40.f, 0.f, 0.f, -50.f, 100.f, 900.f);
	eye[3] = new Eye(camera, 270.f, 0.f, 0.f, 49.f, 800, 100.f, 0.f);
	eye[4] = new Eye(camera, 0, 90, 0, 0, 0, 300, 0);

	eye[0]->setTextures(eyeTextures);
	eye[1]->setTextures(eyeTextures);
	eye[2]->setTextures(eyeTextures);
	eye[3]->setTextures(eyeTextures);
	eye[4]->setTextures(eyeTextures);
}

void MyScene::Update(const double& deltaTime) {
	Scene::Update(deltaTime);
	float x = camera->GetXYZ()[0];
	float z = camera->GetXYZ()[2];
	if (x > -50 && x < -35 && z > -50 && z < -35 && !spaceMode) {
		spaceMode = true;
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		sb->setTextures(spacebox);
		door->visible = false;
		AddObjectToScene(rt);
		AddObjectToScene(eye[0]);
		AddObjectToScene(eye[1]);
		AddObjectToScene(eye[2]);
		AddObjectToScene(eye[3]);
		AddObjectToScene(eye[4]);
	}
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 10000.0);
}
