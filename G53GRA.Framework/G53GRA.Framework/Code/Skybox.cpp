#include "Skybox.h"

Skybox::Skybox()
{
}

void Skybox::setTextures(GLuint* _texids)
{
	texids = _texids;                       // Store texture references in pointer array
	toTexture = true;                       // Assume all loaded correctly
	for (int i = 0; i < 5; i++)             // Check if any textures failed to load (NULL)    
		if (texids[i] == NULL) toTexture = false;   // If one texture failed, do not display any
}
// define display function (to be called by MyScene)
void Skybox::Display()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0.f, -10.f, 0.f);
	glScalef(1000.f, 1000.f, 1000.f);
	drawSkybox();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Skybox::drawSkybox()
{
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texids[0]);
	glBegin(GL_QUADS);
	//left side
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(-1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texids[1]);
	glBegin(GL_QUADS);
	//front side
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(1.f, 0.f, -1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 0.f, 1.f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texids[2]);
	glBegin(GL_QUADS);
	//right side
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(-1.f, 0.f, -1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 0.f, -1.f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texids[3]);
	glBegin(GL_QUADS);
	//back side
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(-1.f, 0.f, 1.f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);


	glBindTexture(GL_TEXTURE_2D, texids[4]);
	glBegin(GL_QUADS);
	// TOP SIDE
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 1.f, -1.f);
	glEnd();
	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}