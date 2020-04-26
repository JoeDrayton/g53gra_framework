#include "TexturedQuad.h"

TexturedQuad::TexturedQuad(const std::string& filename) {
	texID = Scene::GetTexture(filename);
}

void TexturedQuad::Display() {
	glPushMatrix();
	glTranslatef(0.f, -2.f, 0.f);
	glScalef(200.f, 200.f, 200.f);
	DrawQuad();
	glPopMatrix();
}

void TexturedQuad::DrawQuad() {
	glColor3f(0.9f, 1.0f, 0.9f); // green
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(-1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}