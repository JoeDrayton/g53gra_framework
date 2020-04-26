#pragma once
#ifndef ___Skybox__
#define ___Skybox__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <cmath>
#include <string>

using namespace std;

class Skybox :
	public DisplayableObject
{
public:
	Skybox();                                 // constructor
	~Skybox() { };                            // destructor
	void setTextures(GLuint* _texids);
	void Display();                         // overloaded virtual Display function
private:
	void drawSkybox();
	bool toTexture;
	GLuint* texids;
};
#endif

