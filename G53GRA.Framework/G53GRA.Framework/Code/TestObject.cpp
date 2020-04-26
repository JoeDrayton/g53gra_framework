#include "TestObject.h"

TestObject::TestObject()
{
}

// define display function (to be called by MyScene)
void TestObject::Display()
{
	
	//ground
	glPushMatrix();
	glTranslatef(0.f, -2.f, 0.f);
	glColor4f(1.0, 1.0, 0.0, 1.0); // yellow
	box(200.f, 0.1f, 200.f);
	glPopMatrix();
	

	//zombie
	glPushMatrix();
	glTranslatef(0.f, 0.f, -15.f);
	glColor4f(0.0, 1.0, 0.0, 1.0);
	box(2.f, 4.f, 2.f);

	//right arm
	glPushMatrix();
	glRotatef(autorotat, 1.f, 0.f, 0.f);
	glTranslatef(1.f, 0.f, 1.25f);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	box(0.5f, 0.5f, 1.25f);
	glPopMatrix();

	//left arm
	glPushMatrix();
	glRotatef(-autorotat, 1.f, 0.f, 0.f);
	glTranslatef(-1.f, 0.f, 1.25f);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	box(0.5f, 0.5f, 1.25f);
	glPopMatrix();
	glPopMatrix();

	//hero
	glPushMatrix();
	glRotatef(heroRotx, 1.f, 0.f, 0.f);
	glRotatef(heroRoty, 0.f, 1.f, 0.f);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	box(2.f, 4.f, 2.f);

	//right arm
	glPushMatrix();
	glTranslatef(0.75f, 0.f, -1.f);
	glRotatef(45, 0.f, 1.f, 0.f);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	box(0.5f, 0.5f, 1.25f);
	glPopMatrix();

	//left arm
	glPushMatrix();
	glTranslatef(-0.75f, 0.f, -1.f);
	glRotatef(-45, 0.f, 1.f, 0.f);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	box(0.5f, 0.5f, 1.25f);
	glPopMatrix();

	//gun
	glPushMatrix();
	glTranslatef(0.f, 0.f, -1.5f);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	box(0.25f, 0.5f, 0.25f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.5f, -2.f);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	box(0.25f, 0.5f, 1.5f);
	glPopMatrix();

	// bullet
	glPushMatrix();
	glTranslatef(0.f, 0.625f, bulletPosition);
	glColor4f(1.0, 0.0, 1.0, 1.0);
	box(0.125f, 0.125f, 0.25f);
	glPopMatrix();

	glPopMatrix();
}

void TestObject::Update(const double & deltaTime)
{
	autorotat = autorotat + autorotatDirect;
	if (autorotat >= zombieArmMaxAngle || autorotat <= -zombieArmMaxAngle) {
		autorotatDirect = -autorotatDirect;
	}

	if (bulletCD) {
		bulletPosition = bulletPosition - bulletSpeed;
		if (-bulletPosition >= bulletMaxRange) {
			bulletPosition = bulletDefPos;
			bulletCD = false;
		}
	}
	//cout << temp << endl;
}

void TestObject::box(float sx, float sy, float sz)
{
	glPushMatrix();
	glScalef(sx, sy, sz); // scale solid cube by size parameters
	glutSolidCube(1.f);
	//glPushAttrib(GL_COLOR_BUFFER_BIT);
	//glColor4f(0.0, 0.0, 0.0, 1.0);
	//glutWireCube(1.f);
	//glPopAttrib();
	glPopMatrix();
}

void TestObject::HandleKey(unsigned char key, int state, int x, int y)
{

	// z to shoot
	if (state == 1 && key == 'z')
	{
		bulletCD = true;
	}

	if (state == 1 && key == '1')
	{
		heroRotx = 0;
		heroRoty = 0;
	}
}

void TestObject::HandleMouse(int button, int state, int x, int y)
{
	currentButton = button;
	mouseX = x;
	mouseY = y;
}

void TestObject::HandleMouseDrag(int x, int y)
{
	float rx, ry;
	float sensitivity = 1.0f; // speed of the camera moving

	// work out the difference between where the mouse was last used (mouseX, mouseY) to
	// position the view direction and the current position (x, y) the mouse is in
	rx = static_cast<float>(x - mouseX);
	ry = static_cast<float>(y - mouseY);

	// switch on which button was pressed and only do the update if the left button was pressed
	switch (currentButton)
	{
	case GLUT_LEFT_BUTTON:

		// add on the amount of change in to the left and right view direction of the camera
		if (ry > 0)
			heroRotx = heroRotx - sensitivity;
			//add(vd, right, rx*sensitivity);
		else if(ry < 0)
			heroRotx = heroRotx + sensitivity;
			//sub(vd, right, rx*-sensitivity);
		// add on the amount of change in to the up and down view direction of the camera
		if (rx > 0)
			heroRoty = heroRoty - sensitivity;
			//sub(vd, up, ry*sensitivity);
		else if (rx < 0)
			heroRoty = heroRoty + sensitivity;
			//add(vd, up, ry*-sensitivity);
	default:
		break;
	}

	mouseX = x;
	mouseY = y;
}