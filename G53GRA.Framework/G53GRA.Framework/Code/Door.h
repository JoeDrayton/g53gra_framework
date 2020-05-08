#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include <string>

class Door :
	public DisplayableObject,
	public Animation
{
public:
	Door(const std::string& frontFace, const std::string& backFace, const std::string& sideFace, const std::string& portal, Camera* camera);
	~Door() {};
	void Update(const double& deltaTime);
	void DrawPortal();
	void Display();
	bool visible;
	float calculateDistance();

private:
	int rotateAngle;
	int portalAngle;
	void DrawQuad();
	Camera* camera;
	GLint texID[4];
};

