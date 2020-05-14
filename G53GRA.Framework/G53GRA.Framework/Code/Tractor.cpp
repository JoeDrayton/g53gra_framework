#include "Tractor.h"

Tractor::Tractor(GLfloat X, GLfloat Y, GLfloat Z)
	:wheelRotate(0), goTime(false), X(X), Y(Y), Z(Z), rotateX(0), rotateY(-90), rotateZ(2)
{
	axel1 = new Cylinder(1.0, 14.0, 0, 0, 0, 5, -2.5, 1, 40, 10, 10, false);
	axel2 = new Cylinder(1.0, 18.0, 0, 0, 0, 40, 0, -1, 40, 10, 10, false);

	front1 = new Cylinder(5.0, 3.0, 0, 0, 0, 5, -2.5, 0, 20, 20, 20, true);
	front2 = new Cylinder(5.0, 3.0, 0, 0, 0, 5, -2.5, 13, 20, 20, 20, true);
	back1 = new  Cylinder(8.0, 4, 0, 0, 0, 40, 0, -5, 20, 20, 20, true);
	back2 = new  Cylinder(8.0, 4, 0, 0, 0, 40, 0, 17, 20, 20, 20, true);

	frontTrim1 = new Cylinder(3.0, 0.01, 0, 0, 0, 5, -2.5, -0.01, 186, 181, 179, false);
	frontTrim2 = new Cylinder(3.0, 0.01, 0, 0, 0, 5, -2.5, 16.0, 186, 181, 179, false);
	backTrim1 = new Cylinder(5.0, 0.01, 0, 0, 0, 40, 0, -5.01, 186, 181, 179, false);
	backTrim2 = new Cylinder(5.0, 0.01, 0, 0, 0, 40, 0, 21.0, 186, 181, 179, false);

	wheel = new  Cylinder(4.0, 0.5, 90, -30, 0, 30, 16, 8, 10, 10, 10, false);
	wheelShaft = new  Cylinder(0.5, 7, 90, -30, 0, 30, 16, 8, 10, 10, 10, false);

	spout1 = new Cylinder(1.0, 8.0, 90.f, 0.f, 0.f, 10, 18, 4, 10, 10, 10, false);
	spout2 = new Cylinder(0.7, 8.0, 90.f, 0.f, 0.f, 10, 23, 4, 10, 10, 10, false);
}

void Tractor::resetRotation() {
	rotateX = 0;
	rotateY = 0;
	rotateZ = 0;
}

GLfloat* generateColours(GLfloat R, GLfloat G, GLfloat B) {
	GLfloat* colours = new GLfloat[36];
	for (int i = 0; i < 36; i += 3) {
		int random = std::rand() % 20;
		colours[i] = (GLfloat)R/256;
		colours[i+1] = (GLfloat)G/256;
		colours[i+2] = (GLfloat)B/256;
	}
	return colours;
}

void Tractor::DrawTractor() {
	axel1->Display();
	axel2->Display();
	front1->Display();
	front2->Display();
	frontTrim1->Display();
	frontTrim2->Display();

	back1->Display();
	back2->Display();
	backTrim1->Display();
	backTrim2->Display();
	wheel->Display();
	wheelShaft->Display();
	spout1->Display();
	spout2->Display();

	//Main Tractor frame
	DrawCube(15.f, 5.f, 8.f, 30.f, 13.f, 10.f, 0.8f, 0.3f,0.3f); // Engine bit
	DrawCube(35.f, 5.f, 8.f, 20.f, 10.f, 18.f, 0.8f, 0.2f, 0.3f); // Main area

	// Cockpit frames
	DrawCube(25.5f, 18.f, 16.5f, 1.f, 16.f, 1.f, 0.1f, 0.1f, 0.1f);  // Pole 1
	DrawCube(25.5f, 18.f, -0.5f, 1.f, 16.f, 1.f, 0.1f, 0.1f, 0.1f);	 // Pole 2
	DrawCube(44.5f, 18.f, 16.5f, 1.f, 16.f, 1.f, 0.1f, 0.1f, 0.1f); // Pole 3
	DrawCube(44.5f, 18.f, -0.5f, 1.f, 16.f, 1.f, 0.1f, 0.1f, 0.1f); // Pole 4

	DrawCube(35.f, 27.f, 8.f, 20.f, 2.f, 18.f, 0.8f, 0.2f, 0.3f); // Roof
	DrawCube(44.5f, 18.f, 8.f, 1.f, 18.f, 16.f, 0.8f, 0.2f, 0.3f); // Back

	// Seat
	DrawCube(40.f, 15.f, 8.f, 2.f, 8.f, 8.f, 0.45, 0.282, 0.01);
	DrawCube(37.f, 10.f, 8.f, 8.f, 3.f, 8.f, 0.45, 0.282, 0.01);

	// Stairs
	DrawCube(25.5f, 4.5f, 19.f, 1.f, 9.f, 4.f, 0.4, 0.3, 0.3); // Left side
	DrawCube(31.f, 4.5f, 19.f, 1.f, 9.f, 4.f, 0.4, 0.3, 0.3); // Right side
	DrawCube(28.f, 0.5f, 19.f, 5.f, 1.f, 4.f, 0.4, 0.3, 0.3); // Step 1
	DrawCube(28.f, 4.5f, 19.f, 5.f, 1.f, 4.f, 0.4, 0.3, 0.3); // Step 2
	DrawCube(28.f, 8.5f, 19.f, 5.f, 1.f, 4.f, 0.4, 0.3, 0.3); // Step 3

	// Mud flaps rear
	glPushMatrix();
	glRotatef(20, 0.f, 0.f, 1.f);
	DrawCube(35.f, -3.f, 19.f, 6.f, 1.f, 4.f, 0.4, 0.3, 0.3); // Mud flap right
	DrawCube(35.f, -3.f, -3.f, 6.f, 1.f, 4.f, 0.4, 0.3, 0.3); // Mud flap left
	glPopMatrix();

	DrawCube(40.5f, 10.1f, 19.f, 8.f, 1.1f, 4.f, 0.4, 0.3, 0.3); // Mud flap left
	DrawCube(40.5f, 10.1f, -3.f, 8.f, 1.1f, 4.f, 0.4, 0.3, 0.3); // Mud flap left

	glPushMatrix();
	glRotatef(-40, 0.f, 0.f, 1.f);
	DrawCube(30.f, 35.8f, 19.f, 6.f, 1.25f, 4.f, 0.4, 0.3, 0.3); // Mud flap right
	DrawCube(30.f, 35.8f, -3.f, 6.f, 1.25f, 4.f, 0.4, 0.3, 0.3); // Mud flap left
	glPopMatrix();

	DrawCube(20.f, 5.f, 15.f, 7.f, 12.f, 4.f, 0.2, 0.2, 0.2); // Step 3

}

void Tractor::Display() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(X, Y, Z);
	glRotatef(rotateX, 1.f, 0.f, 0.f);
	glRotatef(rotateY, 0.f, 1.f, 0.f);
	glRotatef(rotateZ, 0.f, 0.f, 1.f);
	glScalef(2.0, 2.0, 2.5);
	DrawTractor();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Tractor::Update(const double& deltaTime)
{
	if (goTime) {
		wheelRotate++;
		front1->setRotateZ(wheelRotate);
		front2->setRotateZ(wheelRotate);
		frontTrim1->setRotateZ(wheelRotate);
		frontTrim2->setRotateZ(wheelRotate);
		back1->setRotateZ(wheelRotate);
		back2->setRotateZ(wheelRotate);
		backTrim1->setRotateZ(wheelRotate);
		backTrim2->setRotateZ(wheelRotate);

		if (Y < 80) {
			Y++;
		}
		else {
			Y += sin(wheelRotate /50);
			X = 800 * cos(wheelRotate / 200);
			Z = 800 * sin(wheelRotate / 200);
			rotateY -= 0.28;
			rotateX += 0.4 * sin(wheelRotate/10);
			double deltaX = Z * cos(wheelRotate / 200) - X * sin(wheelRotate / 200);
			double deltaZ = X * cos(wheelRotate / 200) + Z * sin(wheelRotate / 200);
			GLfloat ambience[] = { 0.9f, 0.6f, 0.2f, 1.0f };
			GLfloat diffuse[] = { 0.6f, 0.4f, 0.3f, 1.0f };
			GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			GLfloat position[] = { X, Y + 50, Z + 8, 1.f };
			GLfloat spot_direction1[] = { deltaX, -10.f, deltaZ };
			glLightfv(GL_LIGHT4, GL_AMBIENT, ambience);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
			glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.5f);
			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction1);
			glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 4.f);
			glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 90.f);
			glLightfv(GL_LIGHT4, GL_POSITION, position);
			glEnable(GL_LIGHT4);

			float ambient2[] = { 0.2f, 1.f, 1.f, 1.f };
			float diffuse2[] = { 0.1f, 0.6f, 0.5f, 1.f };
			GLfloat specular2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			GLfloat spot_direction2[] = { deltaX, -10.f, -deltaZ };

			glLightfv(GL_LIGHT5, GL_AMBIENT, ambient2);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse2);
			glLightfv(GL_LIGHT5, GL_SPECULAR, specular2);
			glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.9f);
			glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction2);
			glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 4.f);
			glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 90.f);
			glLightfv(GL_LIGHT5, GL_POSITION, position);
			glEnable(GL_LIGHT5);
		}
	}
}

void Tractor::DrawCube(GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xLength, GLfloat yLength, GLfloat zLength, GLfloat R, GLfloat G, GLfloat B) {
	GLfloat X = xLength / 2;
	GLfloat Y = yLength / 2;
	GLfloat Z = zLength / 2;

	float tractor_colour[]                      // colour reflected by diffuse light
	= { R, G, B, 1.f };         // mid brown
	float tractor_ambient[]                     // ambient colour
	= { R - 0.35f, G - 0.35f, B - 0.35f };         // dark brown
	float tractor_spec[]                        // specular colour
	= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tractor_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tractor_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tractor_spec);   // set colour for specular reflectance

	//GLfloat vertices[] = {
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glColor3f(R, G, B);
		
	// front face
	glNormal3f(0.f, 0.f, 1.f);
	glVertex3f(xPos - X, yPos + Y, zPos + Z); // top left
	glVertex3f(xPos + X, yPos + Y, zPos + Z); // top right
	glVertex3f(xPos + X, yPos - Y, zPos + Z); // bottom right
	glVertex3f(xPos - X, yPos - Y, zPos + Z); // bottom left

		// back face
	glNormal3f(0.f, 0.f, -1.f);
	glVertex3f(xPos - X, yPos + Y, zPos - Z); // top left
	glVertex3f(xPos + X, yPos + Y, zPos - Z); // top right
	glVertex3f(xPos + X, yPos - Y, zPos - Z); // bottom right
	glVertex3f(xPos - X, yPos - Y, zPos - Z); // bottom left
		
		// left face
	glNormal3f(-1.f, 0.f, 0.f);
	glVertex3f(xPos - X, yPos + Y, zPos + Z); // top left
	glVertex3f(xPos - X, yPos + Y, zPos - Z); // top right
	glVertex3f(xPos - X, yPos - Y, zPos - Z); // bottom right
	glVertex3f(xPos - X, yPos - Y, zPos + Z); // bottom left

		// right face
	glNormal3f(1.f, 0.f, 0.f);
	glVertex3f(xPos + X, yPos + Y, zPos + Z); // top left
	glVertex3f(xPos + X, yPos + Y, zPos - Z); // top right
	glVertex3f(xPos + X, yPos - Y, zPos - Z); // bottom right
	glVertex3f(xPos + X, yPos - Y, zPos + Z); // bottom left

		// top face
	glNormal3f(0.f, 1.f, 0.f);
	glVertex3f(xPos - X, yPos + Y, zPos + Z); // top left
	glVertex3f(xPos - X, yPos + Y, zPos - Z); // top right
	glVertex3f(xPos + X, yPos + Y, zPos - Z); // bottom right
	glVertex3f(xPos + X, yPos + Y, zPos + Z); // bottom left
	
		// bottom face
	glNormal3f(0.f, -1.f, 0.f);
	glVertex3f(xPos - X, yPos - Y, zPos + Z); // top left
	glVertex3f(xPos - X, yPos - Y, zPos - Z); // top right
	glVertex3f(xPos + X, yPos - Y, zPos - Z); // bottom right
	glVertex3f(xPos + X, yPos - Y, zPos + Z); // bottom left
	glEnd();

	glDisable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}