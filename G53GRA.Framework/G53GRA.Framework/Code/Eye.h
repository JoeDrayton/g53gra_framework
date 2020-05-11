#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>

class Eye :
	public DisplayableObject,
	public Animation
{
public:
	Eye(Camera* camera, float angle, float rotateX, float rotateY, float rotateZ, float X, float Y, float Z);
	~Eye() {};
	void Update(const double& deltaTime);
	void setTextures(GLuint* _texids);
	void Next(const double& deltaTime);
	void Display();
	bool visible;
	float calculateDistance();

private:
	float angle, rotateX, rotateY, rotateZ, X, Y, Z, index;
	bool forward;
	void DrawQuad();
	Camera* camera;
	GLuint* texids;
	GLuint activeTexture;
};