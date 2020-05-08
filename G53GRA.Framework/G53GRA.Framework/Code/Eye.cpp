#include "Eye.h"

Eye::Eye(Camera* camera, float angle, float rotateX, float rotateY, float rotateZ, float X, float Y, float Z)
	:camera(camera), index(0), forward(true), angle(angle), rotateX(rotateX), rotateY(rotateY), rotateZ(rotateZ), X(X),Y(Y),Z(Z)
{
	
}

void Eye::setTextures(GLuint* _texids)
{
	texids = _texids;                       // Store texture references in pointer array
	activeTexture = texids[0];
}

void Eye::Next(const double& deltaTime) {
	if (fmod(deltaTime, 0.005) < 0.001){
		if (forward && activeTexture < texids[4]) {
			activeTexture++;
		}
		else {
			forward = false;
		}

		if (!forward && activeTexture > texids[0]) {
			activeTexture--;
		}
		else {
			forward = true;
		}
	}
}

void Eye::Update(const double& deltaTime)
{
	if (calculateDistance() < 500) {
		Next(deltaTime);
	}
	else {
		activeTexture = texids[0];
	}
}

void Eye::Display()
{
	glPushMatrix();
	glTranslatef(X, Y, Z);
	glRotatef(rotateX, 1.f, 0.f, 0.f);
	glRotatef(rotateY, 0.f, 1.f, 0.f);
	glRotatef(rotateZ, 0.f, 0.f, 1.f);
	glScalef(75.f, 75.f, 75.f);
	glDisable(GL_LIGHTING);
	DrawQuad();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

float Eye::calculateDistance() {
	float x = camera->GetXYZ()[0] - X;
	float y = camera->GetXYZ()[1] - Y;
	float z = camera->GetXYZ()[2] - Z;
	return (float)sqrt(pow(x, 2) + pow(Y,2) + pow(z, 2));
}

void Eye::DrawQuad()
{
	glColor3f(0.9f, 1.0f, 0.9f); // green
	glRotatef(angle, 0.f, 1.f, 0.f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, activeTexture);
	//front face
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(2.f, 1.f, 0.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(0.f, 1.f, 0.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(2.f, 0.f, 0.f);
	glEnd();

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}

