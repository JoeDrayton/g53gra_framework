#ifndef ___TestObj4__
#define ___TestObj4__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Input.h"
#include "Animation.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

class TestObject :
	public DisplayableObject,
	public Input,
	public Animation
{
public:
	TestObject();                                 // constructor
	~TestObject() { };                            // destructor
	void Display();                         // overloaded virtual Display function
	void Update(const double& deltaTime);	// overloaded virtual Update function
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
private:
	float autorotatDirect = 0.02f;
	float autorotat = 0.f;
	float zombieArmMaxAngle = 15;

	bool bulletCD = false;
	float bulletPosition = -2.5f;
	float bulletSpeed = 0.1f;
	float bulletMaxRange = 50.f;
	float bulletDefPos = -2.5f;

	float heroRotx = 0;
	float heroRoty = 0;
	void box(float sx, float sy, float sz);
	/** Variable to remember mouse click */
	int currentButton;
	/** Previous mouse coordinates */
	GLint mouseX, mouseY;
};
#endif