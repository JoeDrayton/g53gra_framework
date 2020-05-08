#include "Door.h"

Door::Door(const std::string& frontFace,const std::string& backFace,const std::string& sideFace,const std::string& portal, Camera* camera)
	:rotateAngle(0), camera(camera), portalAngle(0)
{
	texID[0] = Scene::GetTexture(frontFace);
	texID[1] = Scene::GetTexture(backFace);
	texID[2] = Scene::GetTexture(sideFace);
	texID[3] = Scene::GetTexture(portal);
	visible = true;
}


void Door::Display() {
	if (visible) {
		glPushMatrix();
		glTranslatef(-50.f, -100.f, -50.f);
		glScalef(25.f, 25.f, 25.f);

		glMatrixMode(GL_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glRotatef(portalAngle++, 0.5, 0.5, 1);
		glTranslatef(-0.5, -0.5, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		DrawPortal();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		DrawQuad();
		glPopMatrix();
	}
}

float Door::calculateDistance() {
	float x = camera->GetXYZ()[0];
	float z = camera->GetXYZ()[2];
	return (float)sqrt(pow(x, 2) + pow(z, 2));
}

void Door::Update(const double& deltaTime)
{
	if (rotateAngle > -90 && calculateDistance() < 50) {
		rotateAngle--;
	}
	else {
		if (rotateAngle < 0 && calculateDistance() > 50) {
			rotateAngle++;
		}
	}
}

void Door::DrawPortal() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID[3]);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 2.f, 0.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(0.f, 2.f, 0.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 0.f, 0.f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}

void Door::DrawQuad() {
	glRotatef(rotateAngle, 0.f, 1.f, 0.f);
	glColor3f(0.9f, 1.0f, 0.9f); // green
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	//front face
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 2.f, 0.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(0.f, 2.f, 0.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 0.f, 0.f);
	glEnd();

	//back face
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glRotated(180, 0.f, 1.f, 0.f);
	glTranslatef(-1.f, 0.f, 0.05f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 2.f, 0.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(0.f, 2.f, 0.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 0.f, 0.f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID[2]);
	//left side
	glRotated(90, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 1.f);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(0.05f, 2.f, 0.0f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(0.f, 2.f, 0.0f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(0.f, 0.f, 0.0f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(0.05f, 0.f, 0.0f);
	glEnd();
	
	//right side
	glRotated(180, 0.f, 1.f, 0.f);
	glTranslatef(-0.05f, 0.f, 1.f);
	glBegin(GL_QUADS);
	 glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(0.05f, 2.f, 0.0f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(0.f, 2.f, 0.0f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(0.f, 0.f, 0.0f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(0.05f, 0.f, 0.0f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}


