#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
// #include "PolygonCounter.h"

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define PI 3.1429												// Value of pi
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))		// To calculate array size

#define WINDOW_TITLE "Graphics Programming Robot Assignment"

// Define Virtual Keycodes
#define VK_KEY_A 0x41
#define VK_KEY_B 0x42
#define VK_KEY_C 0x43
#define VK_KEY_D 0x44
#define VK_KEY_E 0x45
#define VK_KEY_F 0x46
#define VK_KEY_G 0x47
#define VK_KEY_H 0x48
#define VK_KEY_I 0x49
#define VK_KEY_J 0x4A
#define VK_KEY_K 0x4B
#define VK_KEY_L 0x4C
#define VK_KEY_M 0x4D
#define VK_KEY_N 0x4E
#define VK_KEY_O 0x4F
#define VK_KEY_P 0x50
#define VK_KEY_Q 0x51
#define VK_KEY_R 0x52
#define VK_KEY_S 0x53
#define VK_KEY_T 0x54
#define VK_KEY_U 0x55
#define VK_KEY_V 0x56
#define VK_KEY_W 0x57
#define VK_KEY_X 0x58
#define VK_KEY_Y 0x59
#define VK_KEY_Z 0x5A

#define VK_KEY_0 0x30
#define VK_KEY_1 0x31
#define VK_KEY_2 0x32
#define VK_KEY_3 0x33
#define VK_KEY_4 0x34
#define VK_KEY_5 0x35
#define VK_KEY_6 0x36
#define VK_KEY_7 0x37
#define VK_KEY_8 0x38
#define VK_KEY_9 0x39

#define VK_KEY_SPACE 0x20
#define VK_KEY_ESCAPE 0x1B

#define VK_KEY_UP 0x26
#define VK_KEY_DOWN 0x28
#define VK_KEY_LEFT 0x25
#define VK_KEY_RIGHT 0x27

#define VK_KEY_F1 0x70
#define VK_KEY_F2 0x71
#define VK_KEY_F3 0x72
#define VK_KEY_F4 0x73
#define VK_KEY_F5 0x74
#define VK_KEY_F6 0x75
#define VK_KEY_F7 0x76
#define VK_KEY_F8 0x77
#define VK_KEY_F9 0x78
#define VK_KEY_F10 0x79
#define VK_KEY_F11 0x7A
#define VK_KEY_F12 0x7B

/*
 * --------------------------------------------------------------------
 *								Variables
 * --------------------------------------------------------------------
*/

/********************** PROJECTION **********************/
// Variables for projection transformation
float Ptx = 0.0, Pty = 0.0, PtSpeed = 1.0;
float Pry = 0.0, PrSpeed = 1.0;

// Variables for rotation transformation
float rx = 0, ry = 0, rz = 0, rSpeed = 0.0;

//	Variables for lightning
float ambL[3] = { 1.0, 1.0, 1.0 };	//	White color ambient light
float posA[3] = { 0.0, 1.0, 0.0 };	//	Amb light pos (0,1,0) above
float difL[3] = { 1.0, 1.0, 1.0 };	//	White color Dif light 
float posD[3] = { 1.0, 0.0, 0.0 };	//	Dif light pos (1,0,0) right
float ambM[3] = { 0.0, 0.0, 1.0 };	//	Blue color Amb material
float difM[3] = { 1.0, 0.0, 0.0 };	//	Red color Dif material
bool isLightOn = false;				//	is Light on?

// Variables for views (Orthographic and Perspective)
bool isOrtho = false;
double ONear = -10.0, OFar = 10.0;
double PNear = 1.0, PFar = 20.0;
float tx = 0.0, ty = 0.0, tz = 0.0, tSpeed = 1.0;
float rS = 0.0;

/********************** TEXTURE **********************/
// Variables for texture bitmap
GLuint texture = 0; // texture name
BITMAP bmp; // bitmap structure
HBITMAP hBmp = NULL;
//GLuint texArr[10];
int tex = 0;

/********************** ANIMATION **********************/
//	Weapon pickup
bool gunOn = false;
bool swordOn = false;
bool laser = false;
bool magicBall = false;

double sAngle = -1.2, sAngle2 = -0.6;
double sScale = 1;

// ==== MAIN ====
bool isMove = false;
bool isBow = false;

// ==== HEAD ====
float upDownHeadDegree = 0, leftRightHeadDegree = 0, headBound = 0;

// ==== BODY ====
float upDownBodyDegree = 0;

// ==== HAND ====
bool isWeapon = false;
float upDownRightHandDegree = 0, upDownLeftHandDegree = 0;
float leftShoulderDegree = 0, rightShoulderDegree = 0;
float bowLeftHand = 0, bowRightHand = 0;
bool raiseLeftHand = false;

// ==== LEG ====
float leftLegDegree = 0, rightLegDegree = 0;
float movespeed = 0.01;
bool legMove = false;

// ==== FLY FEATURE ====
bool isFly = false, isDiagonalFly = false;

// ==== WALK FEATURE ====
float walkSpeed = 0.001;
float walk = 0;
bool moveForward;

/*
 * --------------------------------------------------------------------
 *					Windows Procedure (Input Messages)
 * --------------------------------------------------------------------
*/
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_KEY_X: //rotate x-axis
			rx = -1.0;
			ry = 0.0;
			rz = 0.0;
			rSpeed = 1;
			break;
		case VK_KEY_Y: //rotate y-axis
			rx = 0.0;
			ry = -1.0;
			rz = 0.0;
			rSpeed = 1;
			break;
		case VK_KEY_Z: //rotate z-axis
			rx = 0.0;
			ry = 0.0;
			rz = -1.0;
			rSpeed = 1;
			break;
		case VK_SPACE: //Reset all the features
			rSpeed = 0.0;

			isMove = false, isBow = false;
			upDownHeadDegree = 0, leftRightHeadDegree = 0, headBound = 0, upDownBodyDegree = 0;
			upDownRightHandDegree = 0, upDownLeftHandDegree = 0, leftShoulderDegree = 0, rightShoulderDegree = 0;
			bowLeftHand = 0, bowRightHand = 0, raiseLeftHand = false;
			leftLegDegree = 0, rightLegDegree = 0;
			isFly = false, isDiagonalFly = false;
			laser = false, magicBall = false;
			sAngle = -1.2, sAngle2 = -0.6, sScale = 1;
			moveForward = false, legMove = false;

			break;

			//  ==== Lighting Control  ====
		case VK_KEY_F3: //Switch ON or OFF the lighting mode 
			isLightOn = !isLightOn;
			break;
		case VK_KEY_W: //Move the light source to top 
			posD[1] += 0.5;
			break;
		case VK_KEY_A: //Move the light source to left
			posD[2] += 0.5;
			break;
		case VK_KEY_S: //Move the light source to bottom 
			posD[1] -= 0.5;
			break;
		case VK_KEY_D: //Move the light source to right 
			posD[2] -= 0.5;
			break;
		case VK_KEY_E: //Move the light source to near 
			posD[3] -= 0.5;
			break;
		case VK_KEY_Q: //Move the light source to far 
			posD[3] += 0.5;
			break;

			//  ==== Projection Control  ====
		case VK_KEY_UP:
			if (isOrtho) {
				if (tz > ONear)
					tz -= tSpeed;
			}
			else {
				if (tz > ONear)
					tz -= tSpeed;
			}
			break;
		case VK_KEY_DOWN:
			if (isOrtho) {
				if (tz < OFar)
					tz += tSpeed;
			}
			else {
				if (tz < PFar)
					tz += tSpeed;
			}
			break;
		case VK_KEY_LEFT:
			if (isOrtho) {
				if (tx > ONear)
					tx -= tSpeed;
			}
			else {
				if (tx > PNear)
					tx -= tSpeed;
			}
			break;
		case VK_KEY_RIGHT:
			if (isOrtho) {
				if (tx < OFar)
					tx += tSpeed;
			}
			else {
				if (tx < PFar)
					tx += tSpeed;
			}
			break;
		case VK_KEY_J:
			Ptx -= PtSpeed;
			break;
		case VK_KEY_L:
			Ptx += PtSpeed;
			break;
		case VK_KEY_I:
			Pry += PrSpeed;
			break;
		case VK_KEY_K:
			Pry -= PrSpeed;
			break;
		case VK_KEY_P:
			isOrtho = false;
			tz = PNear;
			break;
		case VK_KEY_O:
			isOrtho = true;
			break;

			// ==== WEAPON FEATURE ====
		case VK_KEY_1:
			gunOn = !gunOn;
			break;
		case VK_KEY_2:
			swordOn = !swordOn;
			break;
		case VK_KEY_3:	// Toggle magic ball
			magicBall = !magicBall;
			break;
		case VK_KEY_4:	//Toggle laser
			laser = !laser;
			break;

			// ==== ROBOT INTERACTIONS ====
				// Head
		case VK_KEY_G: // move head down
			if (upDownHeadDegree <= 10)
				upDownHeadDegree++;
			break;
		case VK_KEY_T: // move head up
			if (upDownHeadDegree >= -10)
				upDownHeadDegree--;
			break;
		case VK_KEY_F: // move head right
			if (leftRightHeadDegree <= 10)
				leftRightHeadDegree++;
			break;
		case VK_KEY_H: // move head left
			if (leftRightHeadDegree >= -10)
				leftRightHeadDegree--;
			break;
			// Leg
		case VK_KEY_F1: // move left leg
			if (leftLegDegree <= 10) {
				leftLegDegree++;
				rightLegDegree--;
			}
			break;
		case VK_KEY_F2: // move right leg
			if (leftLegDegree >= -10) {
				rightLegDegree++;
				leftLegDegree--;
			}
			break;
			// Hands
				// right hand
		case VK_KEY_B: // To move the right hand up
			if (upDownRightHandDegree <= 5) {
				upDownRightHandDegree += 0.5;
				rightShoulderDegree += 0.05;
				/*upDownRightHandDegree += 0.5;*/
			}
			break;
		case VK_KEY_N: // To move the right hand down
			if (upDownRightHandDegree >= 0) {
				upDownRightHandDegree -= 0.5;
				rightShoulderDegree -= 0.05;
				/*upDownRightHandDegree += 0.5;*/
			}
			break;
			// left hand
		case VK_KEY_C: // To move the left hand up
			if (upDownLeftHandDegree <= 5) {
				upDownLeftHandDegree += 0.5;
				leftShoulderDegree += 0.05;
				/*upDownRightHandDegree += 0.5;*/
			}
			break;
		case VK_KEY_V: // To move the left hand down
			if (upDownLeftHandDegree >= 0) {
				upDownLeftHandDegree -= 0.5;
				leftShoulderDegree -= 0.05;
				/*upDownRightHandDegree += 0.5;*/
			}
			break;

			// ==== RAISE LEFT HAND ====
		case VK_KEY_R:
			raiseLeftHand = !raiseLeftHand;
			break;

			// ==== BOW ====
		case VK_KEY_0:
			if (headBound <= 10 && upDownHeadDegree <= 20) {
				headBound++;
				upDownBodyDegree += 0.5;
				bowLeftHand += 0.5;
				bowRightHand += 0.5;
			}
			break;
		case VK_KEY_9:
			if (headBound >= 0 && upDownHeadDegree >= 0) {
				headBound--;
				upDownBodyDegree -= 0.5;
				bowLeftHand -= 0.5;
				bowRightHand -= 0.5;
			}
			break;
			// ==== WALKING ====
		case VK_KEY_M:
			isMove = !isMove;
			break;
		case VK_KEY_5:				// move forward
			moveForward = true;
			legMove = true;
			break;
		case VK_KEY_6:				// move backward
			moveForward = false;
			legMove = true;
			break;
			// ==== FLY ====
		case VK_KEY_7:
			glLoadIdentity();
			isFly = !isFly;
			isDiagonalFly = false;
			break;
		case VK_KEY_8:
			if (isFly) {
				isDiagonalFly = !isDiagonalFly;
			}
			break;

		default:
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

/*
 * --------------------------------------------------------------------
 *						Windows Initialization
 * --------------------------------------------------------------------
*/

bool initPixelFormat(HDC hdc) {
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * --------------------------------------------------------------------
 *					Texture and Projection Group
 * --------------------------------------------------------------------
*/
// Load and Destroy Texture
GLuint LoadTexture(LPCSTR textureFile) {
	GLuint texture = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	HBITMAP hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), textureFile, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBmp, sizeof(bmp), &bmp);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.bmWidth, bmp.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);

	DeleteObject(hBmp);
	return texture;
}
void DestroyTexture(GLuint textureArray[])
{
	for (int i = 0; i < my_sizeof(textureArray) / my_sizeof(textureArray[0]); i++)
	{
		glDeleteTextures(1, &textureArray[i]);
	}

	glDisable(GL_TEXTURE_2D);
}

// Projection Toggle
void Projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glTranslatef(Ptx, Pty, 0.0);
	glRotatef(Pry, 0.0, 1.0, 0.0);

	if (isOrtho) {
		glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar);
	}
	else {
		gluPerspective(20.0, 1.0 /* width / height of screen */, .0, 1.0);
		glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);
	}
}

/*
 * --------------------------------------------------------------------
 *							Lightning Group
 * --------------------------------------------------------------------
*/
void Lighting()
{
	if (isLightOn)
	{
		glEnable(GL_LIGHTING);	//	Turn on lighting for whole screen
	}
	else
	{
		glDisable(GL_LIGHTING);	//	Turn off lighting for whole screen
	}

	//Light 0 : Red color ambient light at pos(0,1,0) above sphere
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambM);
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	glEnable(GL_LIGHT0);

	//Light 1 : Green color ambient light at pos(0,1,0) above sphere
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difL);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1);
}

/*
 * --------------------------------------------------------------------
 *						Objects Drawing Group
 * --------------------------------------------------------------------
*/

/************************** DRAW 2D OBJECTS **************************/
// Draw Circle - TD: Add Texture Coords
void DrawLineCircle(float xOrigin, float yOrigin, float radius)
{
	glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle <= 2 * PI; angle += (2 * PI) / 30)
	{
		float xPos = xOrigin + radius * cos(angle);
		float yPos = yOrigin + radius * sin(angle);
		glVertex2f(xPos, yPos);
	}
	glEnd();
}
void DrawFullCircle(float xOrigin, float yOrigin, float radius)
{
	glBegin(GL_TRIANGLE_FAN);
	for (float angle = 0; angle <= 2 * PI; angle += (2 * PI) / 30)
	{
		float xPos = xOrigin + radius * cos(angle);
		float yPos = yOrigin + radius * sin(angle);
		glVertex2f(xPos, yPos);
	}
	glEnd();
}

// Draw Square
void DrawLineSquare(float leftXAxis, float topYAxis, float rightXAxis, float botYAxis)
{
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(leftXAxis, botYAxis);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(leftXAxis, topYAxis);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(rightXAxis, topYAxis);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(rightXAxis, botYAxis);
	glEnd();
}
void DrawFullSquare(float leftXAxis, float topYAxis, float rightXAxis, float botYAxis)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(leftXAxis, botYAxis);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(leftXAxis, topYAxis);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(rightXAxis, topYAxis);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(rightXAxis, botYAxis);
	glEnd();
}

// Draw Triangle
/*
 * !! IMPORTANT !!
 * The texture coordinate is set up so that the coord will map it like this
 *
 *            (x2, y2)
 *              ^
 *            /  \
 *          /     \
 *        /________\
 * (x1, y1)       (x3, x3)
 *
 * Write your coordinates with something like this shape in mind
 */
void DrawLineTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(x1, y1);
	glTexCoord2f(0.5, 1.0);
	glVertex2f(x2, y2);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(x3, y3);
	glEnd();
}
void DrawFullTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(x1, y1);
	glTexCoord2f(0.5, 1.0);
	glVertex2f(x2, y2);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(x3, y3);
	glEnd();
}


/************************** DRAW 3D OBJECTS **************************/

// Draw Sphere
void DrawLineSphere(GLdouble radius)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluQuadricTexture(sphere, TRUE);
	gluSphere(sphere, radius, 30, 30);
	gluDeleteQuadric(sphere);
}
void DrawFillSphere(GLdouble radius)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluSphere(sphere, radius, 30, 30);
	gluDeleteQuadric(sphere);
}
void DrawSphere(double radius, GLenum drawStyle) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, true);
	gluQuadricDrawStyle(sphere, drawStyle);
	gluSphere(sphere, radius, 30, 30);
	gluDeleteQuadric(sphere);
}

// Draw Cube
void DrawFullCube(float size)
{
	glBegin(GL_LINE_LOOP);
	// Face 1 : Bottom face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 : Left Face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 : Front Face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, size);
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);

	// Face 4 : Right Face
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(size, size, size);

	// Face 5 : Top Face
	glTexCoord2f(0, 1);
	glVertex3f(size, size, size);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(size, size, 0.0f);

	// Face 6 : Back Face
	glTexCoord2f(0, 1);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glEnd();
}
void DrawFillCube(float size) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 : Left Face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 : Front Face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, size);
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);

	// Face 4 : Right Face
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(size, size, size);

	// Face 5 : Top Face
	glTexCoord2f(0, 1);
	glVertex3f(size, size, size);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(size, size, 0.0f);

	// Face 6 : Back Face
	glTexCoord2f(0, 1);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glEnd();
}
void DrawAdjustableFillCube(float width, float height, float size) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 : Left Face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 : Front Face
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, size);
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);

	// Face 4 : Right Face
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(size, size, size);

	// Face 5 : Top Face
	glTexCoord2f(0, 1);
	glVertex3f(width, height, size);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, size);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, height, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(width, height, 0.0f);

	// Face 6 : Back Face
	glTexCoord2f(0, 1);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glEnd();
}
void DrawCube(float x, float y, float z, float height, float width, float depth, GLenum shape)
{
	// Front face
	glBegin(shape);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(x, y, z + depth);
	glTexCoord2f(1, 1);
	glVertex3f(x, y + height, z + depth);
	glTexCoord2f(1, 0);
	glVertex3f(x, y + height, z);
	glEnd();

	// Right face
	glBegin(shape);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(1, 0);
	glVertex3f(x + width, y, z);
	glTexCoord2f(1, 1);
	glVertex3f(x + width, y, z + depth);
	glTexCoord2f(1, 1);
	glVertex3f(x, y, z + depth);
	glEnd();

	// Back face
	glBegin(shape);
	glTexCoord2f(0, 0);
	glVertex3f(x + width, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(x + width, y + height, z);
	glTexCoord2f(1, 1);
	glVertex3f(x + width, y + height, z + depth);
	glTexCoord2f(1, 0);
	glVertex3f(x + width, y, z + depth);
	glEnd();

	// Left face
	glBegin(shape);
	glTexCoord2f(0, 1);
	glVertex3f(x + width, y + height, z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y + height, z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y + height, z + depth);
	glTexCoord2f(1, 1);
	glVertex3f(x + width, y + height, z + depth);
	glEnd();

	// Top face
	glBegin(shape);
	glTexCoord2f(0, 1);
	glVertex3f(x, y + height, z + depth);
	glTexCoord2f(1, 1);
	glVertex3f(x + width, y + height, z + depth);
	glTexCoord2f(1, 0);
	glVertex3f(x + width, y, z + depth);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z + depth);
	glEnd();

	// Bottom face
	glBegin(shape);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(1, 0);
	glVertex3f(x + width, y, z);
	glTexCoord2f(1, 1);
	glVertex3f(x + width, y + height, z);
	glTexCoord2f(0, 1);
	glVertex3f(x, y + height, z);
	glEnd();
}

// Draw Cone
void DrawLineCone(double radius, double height)
{
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();

	gluQuadricDrawStyle(cone, GLU_LINE);
	gluQuadricTexture(cone, TRUE);
	gluCylinder(cone, radius, 0, height, 30, 30);
	gluDeleteQuadric(cone);
}
void DrawFillCone(double radius, double height)
{
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();

	gluQuadricDrawStyle(cone, GLU_FILL);
	gluQuadricTexture(cone, TRUE);
	gluCylinder(cone, radius, 0, height, 30, 30);
	gluDeleteQuadric(cone);
}
void DrawCone(double topRadius, double height, int slices, int stacks, GLenum drawStyle)
{
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, true);
	gluQuadricDrawStyle(cylinder, drawStyle);
	gluCylinder(cylinder, topRadius, 0, height, slices, stacks);
	gluDeleteQuadric(cylinder);
}

// Draw Cylinder
void DrawLineCylinder(double baseRadius, double topRadius, double height)
{
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluQuadricTexture(cylinder, TRUE);
	gluCylinder(cylinder, baseRadius, topRadius, height, 30, 30);
	gluDeleteQuadric(cylinder);
}
void DrawFillCylinder(double baseRadius, double topRadius, double height)
{
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, TRUE);
	gluCylinder(cylinder, baseRadius, topRadius, height, 30, 30);
	gluDeleteQuadric(cylinder);
}
void DrawCylinder(double topRadius, double baseRadius, int slices, int stacks, double height, GLenum drawStyle) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, drawStyle);
	gluCylinder(cylinder, topRadius, baseRadius, height, slices, stacks);
	gluDeleteQuadric(cylinder);
}

// Draw Pyramid
void DrawLinePyramid(float size, float height) {
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size / 2, height, size / 2);

	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size / 2, height, size / 2);

	glVertex3f(size, 0.0f, size);
	glVertex3f(size / 2, height, size / 2);

	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size / 2, height, size / 2);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}
void DrawFillPyramid(float size, float height) {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(size / 2, height, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.5, 0.5);
	glVertex3f(size / 2, height, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);

	glTexCoord2f(0.5, 0.5);
	glVertex3f(size / 2, height, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.5, 0.5);
	glVertex3f(size / 2, height, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glEnd();
}
void DrawPyramid(float size) {
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);
	// Face 1
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}

//	Draw Prism
void DrawLinePrism(float width, float height, float size) {
	glBegin(GL_LINE_LOOP);
	glVertex3f(-width / 4, 0, size / 2);
	glVertex3f(-width / 4, 0, -size / 2);
	glVertex3f(-3 * width / 4, 0, -size / 2);
	glVertex3f(-3 * width / 4, 0, size / 2);

	glVertex3f(-width / 4, 0, -size / 2);
	glVertex3f(-width / 4, height, -size / 2);
	glVertex3f(-3 * width / 4, height, -size / 2);
	glVertex3f(-3 * width / 4, 0, -size / 2);

	glVertex3f(-width / 4, height, -size / 2);
	glVertex3f(-3 * width / 4, height, -size / 2);
	glVertex3f(-3 * width / 4, 0, size / 2);
	glVertex3f(-width / 4, 0, size / 2);

	glVertex3f(-width / 4, 0, size / 2);
	glVertex3f(-width / 4, height, -size / 2);
	glVertex3f(-width / 4, 0, -size / 2);

	glVertex3f(-3 * width / 4, 0, size / 2);
	glVertex3f(-3 * width / 4, height, -size / 2);
	glVertex3f(-3 * width / 4, 0, -size / 2);
	glEnd();
}
void DrawFillPrism(float width, float height, float size) {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(width / 2, 0, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(width / 2, 0, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-width / 2, 0, -size / 2); 
	glTexCoord2f(1, 0);
	glVertex3f(-width / 2, 0, size / 2);
	
	glTexCoord2f(0, 0);
	glVertex3f(width / 2, 0, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(width / 2, height, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-width / 2, height, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-width / 2, 0, -size / 2);

	glTexCoord2f(0, 1);
	glVertex3f(width / 2, height, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-width / 2, height, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-width / 2, 0, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(width / 2, 0, size / 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex3f(width / 2, 0, size / 2);
	glTexCoord2f(1, 0.5);
	glVertex3f(width / 2, height, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(width / 2, 0, -size / 2);

	glTexCoord2f(0, 0);
	glVertex3f(-width / 2, 0, size / 2);
	glTexCoord2f(1, 0.5);
	glVertex3f(-width / 2, height, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-width / 2, 0, -size / 2);
	glEnd();
}
void DrawFillLeftHalfPrism(float width, float height, float size)
{
	glBegin(GL_QUADS);
	glVertex3f(-width / 2, 0, size / 2);
	glVertex3f(-width / 2, 0, -size / 2);
	glVertex3f(0, 0, -size / 2);
	glVertex3f(0, 0, size / 2);

	glVertex3f(-width / 2, 0, -size / 2);
	glVertex3f(-width / 2, height, -size / 2);
	glVertex3f(0, height, -size / 2);
	glVertex3f(0, 0, -size / 2);

	glVertex3f(-width / 2, height, -size / 2);
	glVertex3f(0, height, -size / 2);
	glVertex3f(0, 0, size / 2);
	glVertex3f(-width / 2, 0, size / 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-width / 2, 0, size / 2);
	glVertex3f(-width / 2, height, -size / 2);
	glVertex3f(-width / 2, 0, -size / 2);

	glVertex3f(0, 0, size / 2);
	glVertex3f(0, height, -size / 2);
	glVertex3f(0, 0, -size / 2);
	glEnd();
}
void DrawFillRightHalfPrism(float width, float height, float size) {
	glBegin(GL_QUADS);
	glVertex3f(width / 2, 0, size / 2);
	glVertex3f(width / 2, 0, -size / 2);
	glVertex3f(0, 0, -size / 2);
	glVertex3f(0, 0, size / 2);

	glVertex3f(width / 2, 0, -size / 2);
	glVertex3f(width / 2, height, -size / 2);
	glVertex3f(0, height, -size / 2);
	glVertex3f(0, 0, -size / 2);

	glVertex3f(width / 2, height, -size / 2);
	glVertex3f(0, height, -size / 2);
	glVertex3f(0, 0, size / 2);
	glVertex3f(width / 2, 0, size / 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(width / 2, 0, size / 2);
	glVertex3f(width / 2, height, -size / 2);
	glVertex3f(width / 2, 0, -size / 2);

	glVertex3f(0, 0, size / 2);
	glVertex3f(0, height, -size / 2);
	glVertex3f(0, 0, -size / 2);
	glEnd();
}
void DrawAdjustableFillRectangularPrism(float width, float height, float size) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom face
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(width, 0.0f, size);
	glVertex3f(width, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 : Left Face
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(0.0f, height, size);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 : Front Face
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, height, size);
	glVertex3f(width, height, size);
	glVertex3f(width, 0.0f, size);

	// Face 4 : Right Face
	glVertex3f(width, 0.0f, size);
	glVertex3f(width, 0.0f, 0.0f);
	glVertex3f(width, height, 0.0f);
	glVertex3f(width, height, size);

	// Face 5 : Top Face
	glVertex3f(width, height, size);
	glVertex3f(0.0f, height, size);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(width, height, 0.0f);

	// Face 6 : Back Face
	glVertex3f(width, height, 0.0f);
	glVertex3f(width, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
}

//	Draw Trapezium
void DrawTriangularPrism(float x, float y, float z, float height, float width, float depth, GLenum shape)
{
	// Front
	glBegin(shape);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x, y + height, z + depth);
	glEnd();

	// Left
	glBegin(shape);
	glVertex3f(x, y + height, z + depth);
	glVertex3f(x, y, z + depth);
	glVertex3f(x, y, z);
	glEnd();

	// Bottom
	glBegin(shape);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + depth);
	glVertex3f(x + width, y, z + depth);
	glVertex3f(x + width, y, z);
	glEnd();

	// Right
	glBegin(shape);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y, z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glEnd();

	// Back
	glBegin(shape);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x, y + height, z + depth);
	glVertex3f(x, y, z + depth);
	glVertex3f(x + width, y, z + depth);
	glEnd();
}

// Draw Cuboid -hvnt use
void drawCuboid(float x, float y, float sz) {
	glBegin(GL_QUADS);
	// Face 1: Bottom
	//glColor3f(1, 0, 0);
	glTexCoord3f(0, 0, 1), glVertex3f(0, 0, sz);
	glTexCoord3f(1, 0, 1), glVertex3f(x, 0, sz);
	glTexCoord3f(1, 0, 0), glVertex3f(x, 0, 0);
	glTexCoord3f(0, 0, 0), glVertex3f(0, 0, 0); // last point of the face will be the 1st point for next face
	// Face 2: Left
	//glColor3f(0, 1, 1);
	glTexCoord3f(0, 0, 0), glVertex3f(0, 0, 0);
	glTexCoord3f(0, 1, 0), glVertex3f(0, y, 0);
	glTexCoord3f(0, 1, 1), glVertex3f(0, y, sz);
	glTexCoord3f(0, 0, 1), glVertex3f(0, 0, sz);
	// Face 3: Front
	//glColor3f(0, 1, 0);
	glTexCoord3f(0, 0, 1), glVertex3f(0, 0, sz);
	glTexCoord3f(0, 1, 1), glVertex3f(0, y, sz);
	glTexCoord3f(1, 1, 1), glVertex3f(x, y, sz);
	glTexCoord3f(1, 0, 1), glVertex3f(x, 0, sz);
	// Face 4: Right
	//glColor3f(1, 0, 1);
	glTexCoord3f(1, 0, 1), glVertex3f(x, 0, sz);
	glTexCoord3f(1, 1, 1), glVertex3f(x, y, sz);
	glTexCoord3f(1, 1, 0), glVertex3f(x, y, 0);
	glTexCoord3f(1, 0, 0), glVertex3f(x, 0, 0);
	// Face 5: Back
	//glColor3f(0, 0, 1);
	glTexCoord3f(1, 0, 0), glVertex3f(x, 0, 0);
	glTexCoord3f(0, 0, 0), glVertex3f(0, 0, 0);
	glTexCoord3f(0, 1, 0), glVertex3f(0, y, 0);
	glTexCoord3f(1, 1, 0), glVertex3f(x, y, 0);
	// Face 6: Top
	//glColor3f(1, 1, 1);
	glTexCoord3f(1, 1, 0), glVertex3f(x, y, 0);
	glTexCoord3f(0, 1, 0), glVertex3f(0, y, 0);
	glTexCoord3f(0, 1, 1), glVertex3f(0, y, sz);
	glTexCoord3f(1, 1, 1), glVertex3f(x, y, sz);
	glEnd();
}

// Draw Fire Sphere
void drawFireSphere(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	//glColor3f(1, 1, 0);
	glRotatef(0.01, 1, 1, 1);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	GLuint texture = LoadTexture("fire.bmp");
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
}

// Draw Cloud
void drawCloud(float size) {
	drawFireSphere(size);
	glPushMatrix();
	{
		glTranslatef(0.2, 0, 0);
		drawFireSphere(size);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.35, 0.1, 0);
		drawFireSphere(size);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.2, 0.2, 0);
		drawFireSphere(size);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0, 0.2, 0);
		drawFireSphere(size);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.15, 0.1, 0);
		drawFireSphere(size);
	}
	glPopMatrix();

	/*drawCirle(0, 0, size);
	drawCirle(0.2, 0, size);

	drawCirle(0.35, 0.1, size);

	drawCirle(0.2, 0.2, size);
	drawCirle(0, 0.2, size);

	drawCirle(-0.15, 0.1, size);*/
}

//	Reference Line
inline void referenceLine() {
	// X-Axis
	glColor3f(1, 0, 0);
	DrawCube(0.0, 0.0, 0.0, 0.01f, 1.0f, 0.01f, GL_LINE_LOOP);
	for (int i = 0; i < 10; i++)
	{
		DrawCube(0.0 + 0.1 * i, 0.0, 0.0, 0.02f, 0.02f, 0.02f, GL_LINE_LOOP);
	}

	// Y-Axis
	glColor3f(0, 1, 0);
	DrawCube(0.0, 0.0, 0.0, 1.0f, 0.01f, 0.01f, GL_LINE_LOOP);
	for (int i = 0; i < 10; i++)
	{
		DrawCube(0.0, 0.0 + 0.1 * i, 0.0, 0.02f, 0.02f, 0.02f, GL_LINE_LOOP);
	}

	// Z-Axis
	glColor3f(0, 0, 1);
	DrawCube(0.0, 0.0, 0.0, 0.01f, 0.01f, 1.0f, GL_LINE_LOOP);
	for (int i = 0; i < 10; i++)
	{
		DrawCube(0.0, 0.0, 0.0 + 0.1 * i, 0.02f, 0.02f, 0.02f, GL_LINE_LOOP);
	}
	// Center Point
	glColor3f(1, 1, 0);
	DrawSphere(0.02, GLU_FILL);
}

/*
 * --------------------------------------------------------------------
 *							Robot Parts
 * --------------------------------------------------------------------
*/

void RobotHead()
{
	glPushMatrix();
	{

		glRotatef(headBound, 1, 0, 0);
		glRotatef(upDownHeadDegree, 1, 0, 0); // rotate up and down
		glRotatef(leftRightHeadDegree, 0, 1, 0); // rotate left and right
		glTranslatef(0, 0, -0.1);

		GLuint headTexArr[21];// Texture Array


		//-----------------Cover the whole head transformation-----------------//
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(-0.1, 0.5, -0.2);
		glScalef(0.7, 0.7, 0.7);
		//-----------------Cover the whole head transformation-----------------//
		//	Jaw
		headTexArr[0] = LoadTexture("peachMetal.bmp");
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		DrawFillPyramid(0.3, -0.1);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[0]);

		//	Face
		headTexArr[1] = LoadTexture("peachMetal.bmp");
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		DrawFillCube(0.3);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[1]);

		//------------------Left Eye------------------//

		headTexArr[2] = LoadTexture("greenMetal.bmp");
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.06, 0.17, 0.0);
		DrawFillSphere(0.05);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[2]);

		//------------------Right Eye------------------//

		headTexArr[3] = LoadTexture("greenMetal.bmp");
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.24, 0.17, 0.0);
		DrawFillSphere(0.05);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[3]);

		//	Hair
		//------------------Left side hair piece------------------//

		headTexArr[4] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.0, 1.0, 1.0);
		glTranslatef(-0.05, 0.0, 0.0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(0.05, 0.3, 0.0);
		DrawFillPrism(-0.15, -0.4, 0.1);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[4]);


		headTexArr[5] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.5, 0.0);
		glTranslatef(0.45, 0.0, 0.0);
		glTranslatef(0.0, 0.1, 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.01, 0.0, 0.0);
		glRotatef(45, 1.0, 0.0, 0.0);
		DrawFillLeftHalfPrism(0.2, 0.1, 0.4);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[5]);

		//------------------Right side hair piece------------------//
		headTexArr[6] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.0, 1.0, 1.0);
		glTranslatef(0.35, 0.0, 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(-0.05, 0.3, 0.0);
		DrawFillPrism(-0.15, -0.4, 0.1);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[6]);

		headTexArr[7] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.5, 0.0);
		glTranslatef(-0.15, 0.0, 0.0);
		glTranslatef(0.0, 0.1, 0.0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(0.08, 0.0, 0.0);
		glRotatef(45, 1.0, 0.0, 0.0);
		DrawFillLeftHalfPrism(0.2, 0.1, 0.4);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[7]);

		//------------------Left Bangs------------------//
		headTexArr[8] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(1.0, 0.0, 1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, -0.25);
		DrawFillLeftHalfPrism(0.05, -0.15, 0.1);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[8]);

		//------------------Right Bangs------------------//
		headTexArr[9] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(1.0, 0.0, 1.0);
		glTranslatef(0.3, 0.0, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glRotatef(-90, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, -0.25);
		DrawFillRightHalfPrism(0.05, -0.15, 0.1);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[9]);

		//------------------Top Hair------------------//
		headTexArr[10] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		glTranslatef(0, 0.001, 0);
		//glColor3f(0.5, 0.0, 0.0);
		glTranslatef(0.0, 0.3, 0.0);
		glTranslatef(0.0, 0.0, -0.05);
		glTranslatef(-0.1, 0.0, 0.0);
		DrawFillPyramid(0.5, 0.15);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[10]);

		//------------------Back Hair------------------//
		headTexArr[11] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.5, 0.0, 0.0);
		DrawCube(0, 0.0, 0.3, 0.3, 0.3, 0.15, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[11]);

		headTexArr[12] = LoadTexture("tealGreenMetallic.bmp");
		//	Left
		glPushMatrix();
		//glColor3f(0.0, 1.0, 0.5);
		glRotatef(-90, 0, 1, 0);
		DrawCube(0.15, 0.0, 0, 0.3, 0.3, 0.1, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[12]);

		headTexArr[13] = LoadTexture("tealGreenMetallic.bmp");
		//	Right
		glPushMatrix();
		//glColor3f(0.0, 1.0, 0.5);
		glRotatef(90, 0, 1, 0);
		DrawCube(-0.45, 0.0, 0.3, 0.3, 0.3, 0.1, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[13]);

		//------------------Hairband------------------//
		//	Left
		headTexArr[14] = LoadTexture("pinkMetal.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.3, 0.5);
		DrawCube(-0.1, 0.3, 0.25, 0.2, 0.02, 0.05, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[14]);


		headTexArr[15] = LoadTexture("pinkMetal.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.3, 0.5);
		DrawCube(-0.05, 0.3, 0.25, 0.2, 0.02, 0.05, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[15]);
		// glPushMatrix();
		// glColor3f(0.0,0.3,0.5);
		// glTranslatef(0.0,0.38, 0.0);
		// glTranslatef(0.0,0.0, 0.2);
		// glTranslatef(-0.075,0.0, 0.0);
		// glRotatef(90, 1.0, 0.0, 0.0);
		// DrawFillLeftHalfPrism(0.05, 0.15,0.15);
		// glPopMatrix();

		// glPushMatrix();
		// glColor3f(0.0,0.3,0.5);
		// glTranslatef(0.0,0.38, 0.0);
		// glTranslatef(0.0,0.0, 0.25);
		// glTranslatef(-0.025,0.0, 0.0);
		// glRotatef(90, 1.0, 0.0, 0.0);
		// DrawFillLeftHalfPrism(0.05, 0.15,0.15);
		// glPopMatrix();

		//	Right
		headTexArr[16] = LoadTexture("pinkMetal.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.3, 0.5);
		DrawCube(0.38, 0.3, 0.25, 0.2, 0.02, 0.05, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[16]);


		headTexArr[17] = LoadTexture("pinkMetal.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.3, 0.5);
		DrawCube(0.33, 0.3, 0.25, 0.2, 0.02, 0.05, GL_QUADS);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[17]);

		// glPushMatrix();
		// glColor3f(0.0,0.3,0.5);
		// glTranslatef(0.0,0.38, 0.0);
		// glTranslatef(0.0,0.0, 0.2);
		// glTranslatef(0.4,0.0, 0.0);
		// glRotatef(90, 1.0, 0.0, 0.0);
		// DrawFillLeftHalfPrism(0.05, 0.15,0.15);
		// glPopMatrix();

		// glPushMatrix();
		// glColor3f(0.0,0.3,0.5);
		// glTranslatef(0.0,0.38, 0.0);
		// glTranslatef(0.0,0.0, 0.25);
		// glTranslatef(0.35,0.0, 0.0);
		// glRotatef(90, 1.0, 0.0, 0.0);
		// DrawFillLeftHalfPrism(0.05, 0.15,0.15);
		// glPopMatrix();

		//------------------Twin Tail------------------//
		//	Left
		headTexArr[18] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.0, 0.2);
		glTranslatef(0.0, 0.2, 0.0);
		glTranslatef(0.0, 0.0, 0.2);
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -0.2);
		glTranslatef(0.0, 0.1, 0.0);
		DrawFillLeftHalfPrism(0.2, 0.3, 0.2);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[18]);

		//	Right
		headTexArr[19] = LoadTexture("tealGreenMetallic.bmp");
		glPushMatrix();
		//glColor3f(0.0, 0.0, 0.2);
		glTranslatef(0.0, 0.2, 0.0);
		glTranslatef(0.0, 0.0, 0.2);
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -0.5);
		glTranslatef(0.1, 0.0, 0.0);
		glTranslatef(0.0, 0.1, 0.0);
		DrawFillLeftHalfPrism(0.2, 0.3, 0.2);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[19]);

		//	Neck

		headTexArr[20] = LoadTexture("peachMetal.bmp");
		glPushMatrix();
		//glColor3f(0.0, 1.0, 0.0);
		glTranslatef(0.15, 0.0, 0.25);
		glRotatef(90, 1.0, 0.0, 0.0);
		DrawFillCylinder(0.05, 0.05, 0.2);
		glPopMatrix();
		glDeleteTextures(1, &headTexArr[20]);
		//-----------------Cover the whole head transformation-----------------//
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

void RobotBody()
{

	GLuint bodyTexArr[25];

	//-----------------Cover the whole body transformation-----------------//
	glPushMatrix();
	glRotatef(upDownBodyDegree, 1, 0, 0);
	//glTranslatef(0.5, 0, 0);

	// glScalef(4.0, 4.0, 4.0);
	//-----------------Cover the whole body transformation-----------------//

	// Body Base
	bodyTexArr[0] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.5, 0.5);
	DrawCube(-0.15, 0.1, -0.10, 0.3, 0.3, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[0]);


	bodyTexArr[1] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.2, 0.5);
	DrawCube(-0.125, -0.15, -0.10, 0.25, 0.25, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[1]);

	//----------------------------------------Armor----------------------------------------//
	//	Left
	bodyTexArr[2] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.1, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(-360, 0, 1, 0);
	glTranslatef(-0.4, 0.4, 0);
	DrawFillPrism(0.1, 0.05, 0.1);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[2]);

	bodyTexArr[3] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.6, 0.1);
	DrawCube(0.05, 0.4, -0.1, 0.05, 0.1, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[3]);

	//	Right
	bodyTexArr[4] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.1, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(-360, 0, 1, 0);
	glTranslatef(-0.6, 0.4, 0);
	DrawFillPrism(0.1, 0.05, 0.1);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[4]);

	bodyTexArr[5] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.6, 0.1);
	DrawCube(-0.15, 0.4, -0.1, 0.05, 0.1, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[5]);

	//-------------------------------------------------Back-------------------------------------------------//
	//	Left Part
	bodyTexArr[6] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.2, 1.0);
	DrawCube(0.05, 0.1, -0.15, 0.3, 0.1, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[6]);

	bodyTexArr[7] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.1, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.4, 0.4, 0.125);
	DrawFillPrism(0.1, 0.05, 0.05);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[7]);

	//	Center Part
	bodyTexArr[8] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.8, 0.2, 1.0);
	DrawCube(-0.05, 0.1, -0.15, 0.2, 0.1, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[8]);

	//	Right Part
	bodyTexArr[9] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.2, 1.0);
	DrawCube(-0.15, 0.1, -0.15, 0.3, 0.1, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[9]);

	bodyTexArr[10] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.1, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(0.6, 0.4, 0.125);
	DrawFillPrism(0.1, 0.05, 0.05);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[10]);

	// //-----------------------------------------------Chest Area---------------------------------------------//
	//------------------Center Side------------------//
	//	Upper Part
	bodyTexArr[11] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.2, 0.1, 0.3);
	glTranslatef(-0.15, 0.1, 0.1001);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.15, 0, -0.25);
	DrawFillPrism(0.2, 0.15, -0.1);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[11]);

	//	Lower Part
	bodyTexArr[12] = LoadTexture("tealGreenMetallic.bmp");
	glPushMatrix();
	//glColor3f(0.6, 0.1, 0.3);
	glTranslatef(-0.15, 0.1, 0.1001);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.15, 0, -0.1);
	DrawFillPrism(0.2, 0.15, 0.2);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[12]);

	//	Left Part
	bodyTexArr[13] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.8, 0.1);
	DrawCube(0.1, 0.1, 0.1, 0.3, 0.05, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[13]);

	//	Right Part
	bodyTexArr[14] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.8, 0.1);
	DrawCube(-0.15, 0.1, 0.1, 0.3, 0.05, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[14]);

	//	Waist
	//	Front
	bodyTexArr[15] = LoadTexture("tealGreenMetallic.bmp");
	glPushMatrix();
	//glColor3f(0.3, 0.2, 0.2);
	DrawCube(-0.125, 0, 0.1, 0.05, 0.25, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[15]);

	//`Left Side
	bodyTexArr[16] = LoadTexture("tealGreenMetallic.bmp");
	glPushMatrix();
	//glColor3f(0.3, 0.2, 0.2);
	glRotatef(90, 0, 1, 0);
	DrawCube(-0.125, 0, 0.1, 0.05, 0.25, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[16]);

	//	Back Side
	bodyTexArr[17] = LoadTexture("tealGreenMetallic.bmp");
	glPushMatrix();
	//glColor3f(0.3, 0.2, 0.2);
	glRotatef(180, 0, 1, 0);
	DrawCube(-0.125, 0, 0.1, 0.05, 0.25, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[17]);

	//	Right Side
	bodyTexArr[18] = LoadTexture("tealGreenMetallic.bmp");
	glPushMatrix();
	glColor3f(0.3, 0.2, 0.2);
	glRotatef(-90, 0, 1, 0);
	DrawCube(-0.125, 0, 0.1, 0.05, 0.25, 0.05, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[18]);

	//	Skirt
	bodyTexArr[19] = LoadTexture("tealGreenMetallic.bmp");
	glPushMatrix();
	glColor3f(0.6, 0.2, 0.5);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0.0, -0.2);
	DrawFillCylinder(0.25, 0.15, 0.15);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[19]);

	//	Pelvis
	//	Left
	bodyTexArr[20] = LoadTexture("blackMetal.bmp");
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.1, -0.15, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	DrawFillPrism(0.2, 0.05, 0.15);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[20]);

	//	Right
	bodyTexArr[21] = LoadTexture("blackMetal.bmp");
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.1, -0.15, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	DrawFillPrism(0.2, 0.05, -0.15);
	glPopMatrix();
	glDeleteTextures(1, &bodyTexArr[21]);

	//-----------------Cover the whole body transformation-----------------//
	glPopMatrix();
}

void RobotRightArm()
{
	GLuint rightArmTexArr[10];
	//-----------------Cover the whole Right arm transformation-----------------//
	glPushMatrix();
	glRotatef(upDownRightHandDegree, 1, 0, 0);
	glRotatef(-rightShoulderDegree, 1, 0, 0);


	if (swordOn) {
		glTranslatef(0, 0.1, -0.25);
		glRotatef(50, 1, 0, 0);
	}


	glRotatef(bowRightHand, 1, 0, 0);

	//------------------Right------------------//
	//	Upper Armor
	rightArmTexArr[0] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.1, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0, 0.4, 0.2);
	DrawFillPrism(0.15, 0.15, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[0]);

	//	Shoulder
	rightArmTexArr[1] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.2, 0.2, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0, 0.4, 0.2);
	DrawFillPrism(-0.15, -0.15, -0.3);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[1]);

	//-----------------Cover the Right arm transformation-----------------//
	glPushMatrix();

	//-----------------Cover the Right arm transformation-----------------//
	//	Arm Upper

	rightArmTexArr[2] = LoadTexture("peachMetal.bmp");
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0);
	DrawCube(0.2, 0.09, -0.05, 0.3, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[2]);

	//	Arm Center
	rightArmTexArr[3] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.1, 0);
	DrawCube(0.2, -0.01, -0.05, 0.1, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[3]);

	//	Arm Bottom
	glPushMatrix();
	rightArmTexArr[4] = LoadTexture("darkGrey.bmp");
	//glColor3f(0.2, 0.5, 0);
	DrawCube(0.2, -0.21, -0.05, 0.2, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[4]);
	
	//	Left Side
	rightArmTexArr[5] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.2, 0.5);
	glTranslatef(0.312, -0.21, 0);
	glRotatef(90, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[5]);
	
	//	Back Side
	rightArmTexArr[6] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.2, 0.2);
	glTranslatef(0.25, -0.21, -0.07);
	glRotatef(-180, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[6]);
	
	//	Front Side
	rightArmTexArr[7] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.5, 0.8);
	glTranslatef(0.25, -0.21, 0.07);
	glRotatef(-360, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[7]);
	
	//	Right Side
	rightArmTexArr[8] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.5);
	glTranslatef(0.185, -0.21, 0);
	glRotatef(-90, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[8]);

	//	Hands
	rightArmTexArr[9] = LoadTexture("peachMetal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.9);
	glTranslatef(0.25, -0.21, 0);
	DrawSphere(0.05, GLU_FILL);
	glPopMatrix();
	glDeleteTextures(1, &rightArmTexArr[9]);

	//-----------------Cover the Right arm transformation-----------------//
	glPopMatrix();
	glPopMatrix();
	//-----------------Cover the whole Right arm transformation-----------------//
}

void RobotLeftArm()
{
	GLuint leftArmTexArr[10];

	//-----------------Cover the whole Left arm transformation-----------------//
	glPushMatrix();
	glRotatef(-upDownLeftHandDegree, 1, 0, 0);
	glRotatef(-leftShoulderDegree, 1, 0, 0);


	if (raiseLeftHand) {
		glTranslatef(0, 0.7, 0);
		glRotatef(180, 1, 0, 0);
	}

	if (gunOn) {
		glTranslatef(0, 0.1, 0.25);
		glRotatef(-50, 1, 0, 0);
	}

	glRotatef(bowLeftHand, 1, 0, 0);

	//------------------Left------------------//
	//	Upper Armor

	leftArmTexArr[0] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.1, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0.4, -0.8);
	DrawFillPrism(0.15, 0.15, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[0]);

	//	Shoulder
	leftArmTexArr[1] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.2, 0.2, 0.5);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0.4, -0.8);
	DrawFillPrism(-0.15, -0.15, -0.3);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[1]);

	glDisable(GL_TEXTURE_2D);

	//-----------------Cover the Left arm transformation-----------------//
	glPushMatrix();

	//-----------------Cover the Left arm transformation-----------------//
	//	Arm Upper
	leftArmTexArr[2] = LoadTexture("peachMetal.bmp");
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0);
	DrawCube(-0.3, 0.09, -0.05, 0.3, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[2]);

	//	Arm Center
	leftArmTexArr[3] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.1, 0);
	DrawCube(-0.3, -0.01, -0.05, 0.1, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[3]);

	//	Arm Bottom
	leftArmTexArr[4] = LoadTexture("darkGrey.bmp");
	glPushMatrix();
	//glColor3f(0.2, 0.5, 0);
	DrawCube(-0.3, -0.21, -0.05, 0.2, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[4]);
	//	Right Side
	leftArmTexArr[5] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.2, 0.5);
	glTranslatef(-0.312, -0.21, 0);
	glRotatef(-90, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[5]);
	//	Back Side
	leftArmTexArr[6] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.2, 0.2);
	glTranslatef(-0.25, -0.21, -0.07);
	glRotatef(-180, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[6]);
	//	Front Side
	leftArmTexArr[7] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.5, 0.8);
	glTranslatef(-0.25, -0.21, 0.07);
	glRotatef(-360, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[7]);
	//	Left Side
	leftArmTexArr[8] = LoadTexture("darkTeal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.5);
	glTranslatef(-0.185, -0.21, 0);
	glRotatef(90, 0, 1, 0);
	DrawFillPrism(0.1, 0.2, 0.025);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[8]);

	//	Hands
	leftArmTexArr[9] = LoadTexture("peachMetal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.9);
	glTranslatef(-0.25, -0.21, 0);
	DrawSphere(0.05, GLU_FILL);
	glPopMatrix();
	glDeleteTextures(1, &leftArmTexArr[9]);
	glPopMatrix();
	glPopMatrix();
	//-----------------Cover the whole Left arm transformation-----------------//

	glPopMatrix();
}

void RobotLeg() 
{
	GLuint rightLegTexArr[10];
	GLuint leftLegTexArr[10];

	//-----------------Cover the whole leg transformation-----------------//
	glPushMatrix();
	// glScalef(4.0, 4.0, 4.0);
	//-----------------Cover the whole leg transformation-----------------//

	//-----------------Cover the whole Right leg transformation-----------------//
	glPushMatrix();
	glRotatef(-rightLegDegree, 1, 0, 0);

	//------------------Right Leg------------------//
	//	Thigh
	rightLegTexArr[0] = LoadTexture("whiteMetallicTexture.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.5, 0.5);
	DrawCube(0.05, -0.35, -0.10, 0.2, 0.1, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[0]);

	//	Left Side
	rightLegTexArr[1] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.9, 0.1, 0.5);
	glTranslatef(0.165, -0.15, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-180, 1, 0, 0);
	DrawFillPrism(0.2, 0.2, -0.02);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[1]);

	rightLegTexArr[2] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.9, 0.1, 0.5);
	glTranslatef(0.04, -0.15, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-180, 1, 0, 0);
	DrawFillPrism(0.2, 0.2, -0.02);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[2]);

	//	Knee
	rightLegTexArr[3] = LoadTexture("peachMetal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.8, 0.5);
	DrawCube(0.05, -0.55, -0.10, 0.2, 0.1, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[3]);

	//	Ankle
	rightLegTexArr[4] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.8, 0.5, 0.5);
	DrawCube(0.05, -0.85, -0.10, 0.3, 0.1, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[4]);

	//	Left Side
	rightLegTexArr[5] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.9, 0.1, 0.5);
	glTranslatef(0.175, -0.85, 0);
	glRotatef(90, 0, 1, 0);
	DrawFillPrism(0.2, 0.3, 0.05);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[5]);

	//	Feet
	rightLegTexArr[6] = LoadTexture("redMetal.bmp");
	glPushMatrix();
	//glColor3f(0.3, 0.5, 0.5);
	DrawCube(0.05, -0.85, 0.10, 0.05, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[6]);

	rightLegTexArr[7] = LoadTexture("pinkMetal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.1, 0.5);
	glTranslatef(0.1, -0.8, 0.15);
	DrawFillPrism(0.1, 0.1, 0.1);
	glPopMatrix();
	glDeleteTextures(1, &rightLegTexArr[7]);
	glPopMatrix();
	//-----------------Cover the whole Right leg transformation-----------------//

	//-----------------Cover the whole Left leg transformation-----------------//
	glPushMatrix();
	glRotatef(-leftLegDegree, 1, 0, 0);

	//------------------Left Leg------------------//
	//	Thigh
	leftLegTexArr[0] = LoadTexture("whiteMetallicTexture.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.5, 0.5);
	DrawCube(-0.15, -0.35, -0.10, 0.2, 0.1, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[0]);

	//	Right Side
	leftLegTexArr[1] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.9, 0.1, 0.5);
	glTranslatef(-0.165, -0.15, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-180, 1, 0, 0);
	DrawFillPrism(0.2, 0.2, -0.02);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[1]);

	leftLegTexArr[2] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.9, 0.1, 0.5);
	glTranslatef(-0.04, -0.15, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-180, 1, 0, 0);
	DrawFillPrism(0.2, 0.2, -0.02);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[2]);

	//	Knee
	leftLegTexArr[3] = LoadTexture("peachMetal.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.8, 0.5);
	DrawCube(-0.15, -0.55, -0.10, 0.2, 0.1, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[3]);

	//	Ankle
	leftLegTexArr[4] = LoadTexture("darkGreyMetal.bmp");
	glPushMatrix();
	//glColor3f(0.8, 0.5, 0.5);
	DrawCube(-0.15, -0.85, -0.10, 0.3, 0.1, 0.2, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[4]);

	//	Right Side
	leftLegTexArr[5] = LoadTexture("whiteMetal.bmp");
	glPushMatrix();
	//glColor3f(0.9, 0.1, 0.5);
	glTranslatef(-0.175, -0.85, 0);
	glRotatef(-90, 0, 1, 0);
	DrawFillPrism(0.2, 0.3, 0.05);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[5]);

	//	Feet
	leftLegTexArr[6] = LoadTexture("redMetal.bmp");
	glPushMatrix();
	//glColor3f(0.3, 0.5, 0.5);
	DrawCube(-0.15, -0.85, 0.10, 0.05, 0.1, 0.1, GL_QUADS);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[6]);

	leftLegTexArr[7] = LoadTexture("pinkMetal.bmp");
	glPushMatrix();
	//glColor3f(0.1, 0.1, 0.5);
	glTranslatef(-0.1, -0.8, 0.15);
	DrawFillPrism(0.1, 0.1, 0.1);
	glPopMatrix();
	glDeleteTextures(1, &leftLegTexArr[7]);
	glPopMatrix();
	//-----------------Cover the whole Left leg transformation-----------------//

	//-----------------Cover the whole leg transformation-----------------//
	glPopMatrix();
}

//	Weapon: Loudspeaker
void LoudSpeaker()
{
	GLuint speakerTexArr[10];

	glPushMatrix();
	glTranslatef(-0.25, 0, 0.45);
	glRotatef(90, 0, 0, 1);
	//glRotatef(180, 1, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	//-----------------Cover the whole head transformation-----------------//
	//	Outer
	speakerTexArr[0] = LoadTexture("blackPlastic.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.3, 1.0);
	DrawFillCylinder(0.1, 0.3, 0.5);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[0]);

	//	Inner
	speakerTexArr[1] = LoadTexture("blackPlastic.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.3, 1.0);
	glTranslatef(0, 0, -0.1);
	DrawFillCylinder(0.1, 0.1, 0.6);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[1]);


	//	Front
	speakerTexArr[2] = LoadTexture("tealPlastic.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0, 0, 0.5);
	DrawFillSphere(0.1);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[2]);

	//	Handle
	speakerTexArr[3] = LoadTexture("greyPlastic.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.0);
	glRotatef(-90, 0, 1.0, 0);
	DrawFillCylinder(0.1, 0.05, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[3]);

	speakerTexArr[4] = LoadTexture("blackPlastic.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.0);
	glRotatef(-90, 0, 1.0, 0);
	glTranslatef(0.0, 0, 0.3);
	DrawFillSphere(0.05);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[4]);

	speakerTexArr[5] = LoadTexture("blackPlastic.bmp");
	glPushMatrix();
	//glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, 0, -0.3);
	DrawFillCylinder(0.05, 0.1, 0.2);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[5]);

	speakerTexArr[6] = LoadTexture("blackPlastic.bmp");
	glPushMatrix();
	//glColor3f(1.0, 0.0, 1.0);
	glTranslatef(0.0, 0, -0.3);
	DrawFillSphere(0.05);
	glPopMatrix();
	glDeleteTextures(1, &speakerTexArr[6]);
	//-----------------Cover the whole loudspeaker transformation-----------------//
	glPopMatrix();
}
//	Weapon: Green Onions
void OnionSword()
{
	GLuint onionTexArr[10];

	glPushMatrix();

	glTranslatef(0.25, 0, -0.5);
	glRotatef(90, 0, 0, 1);
	glRotatef(135, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	//-----------------Cover the whole onion sword transformation-----------------//
	//	Handle
	onionTexArr[0] = LoadTexture("whiteOnion.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.3, 0.3);
	DrawFillCylinder(0.03, 0.03, 0.7);
	glPopMatrix();
	glDeleteTextures(1, &onionTexArr[0]);

	onionTexArr[1] = LoadTexture("whiteOnion.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.1, 0.3);
	glTranslatef(0, 0.0, 0.7);
	DrawFillSphere(0.03);
	glPopMatrix();
	glDeleteTextures(1, &onionTexArr[1]);

	//	Upper part:Left
	onionTexArr[2] = LoadTexture("greenVege.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.3, 0.1);
	glRotatef(-165, 1, 0, 0);
	DrawFillCylinder(0.03, 0.03, 0.4);
	glPopMatrix();
	glDeleteTextures(1, &onionTexArr[2]);

	onionTexArr[3] = LoadTexture("greenVege.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.1, 0.1);
	glRotatef(-165, 1, 0, 0);
	glTranslatef(0, 0, 0.4);
	DrawFillCone(0.03, 0.1);
	glPopMatrix();
	glDeleteTextures(1, &onionTexArr[3]);

	//	Upper part:Right
	onionTexArr[4] = LoadTexture("greenVege.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.3, 0.5);
	glRotatef(165, 1, 0, 0);
	DrawFillCylinder(0.03, 0.03, 0.2);
	glPopMatrix();
	glDeleteTextures(1, &onionTexArr[4]);

	onionTexArr[5] = LoadTexture("greenVege.bmp");
	glPushMatrix();
	//glColor3f(0.0, 0.1, 0.1);
	glRotatef(165, 1, 0, 0);
	glTranslatef(0, 0, 0.2);
	DrawFillCone(0.03, 0.1);
	glPopMatrix();
	glDeleteTextures(1, &onionTexArr[5]);
	//-----------------Cover the whole onion sword transformation-----------------//
	glPopMatrix();
}
//	Weapon Trigger
void WeaponTrigger()
{
	if (gunOn)
	{
		RobotLeftArm();

		LoudSpeaker();
		if (laser) {
			glColor3f(1, 0, 0);
			/*glTranslatef(0, 2.3, 2.3);
			glRotatef(-90, 1, 0, 0);*/

			glPushMatrix();
			{
				glTranslatef(-0.25, 0, 0.5);
				//glRotatef(90, 1, 0, 0);
				DrawFillCylinder(0.01, 0.01, 0.6);
			}
			glPopMatrix();
		}
	}
	else if (swordOn)
	{
		RobotRightArm();

		OnionSword();
		if (magicBall) {
			sAngle -= 0.02;

			glPushMatrix();
			glScalef(sScale, sScale, sScale);
			glColor3f(1, 0, 0);
			//glRotatef(45, 1, 0, 0);  // rotate the magic ball 45 degrees around the x-axis
			glTranslatef(0.25, 0.3, sAngle);  // translate the magic ball upwards in the y direction
			DrawSphere(0.05, GLU_FILL);
			glPopMatrix();

			sAngle2 -= 0.01;

			glPushMatrix();
			glScalef(sScale, sScale, sScale);
			glColor3f(1, 0, 0);
			//glRotatef(45, 1, 0, 0);  // rotate the magic ball 45 degrees around the x-axis
			glTranslatef(0.25, 0.3, sAngle2);  // translate the magic ball upwards in the y direction
			DrawSphere(0.05, GLU_FILL);
			glPopMatrix();

			if (sAngle < -10) {
				//reset 
				sScale = 0;
				sAngle = -1.2;
				sAngle2 = -0.6;
			}
			else {
				sScale = 1;
			}
		}

	}
}

void robotDisplay() {
	if (isMove) {
		/*glRotatef(-0.1, 0, 0, 0);
		glTranslatef(0, 0, 0.1);*/
		if (isMove && moveForward)
		{
			walk += walkSpeed;
		}
		else if (isMove && !moveForward)
		{
			walk -= walkSpeed;
		}
	}
	else
	{
		walk = 0;
	}

	if (legMove)
	{
		leftLegDegree += movespeed;
		rightLegDegree -= movespeed;
		if (leftLegDegree >= 10)
		{
			movespeed = -movespeed;
		}
		else if (leftLegDegree <= -10)
		{
			movespeed = -movespeed;
		}
	}

	if (isFly) {
		glTranslatef(0, 0.001, 0);
	}

	if (isDiagonalFly) {

		glTranslatef(0, 0.001, 0);
		glLoadIdentity();
		glRotatef(45, 1, 0, 0);
	}

	// Draw Robot Here
	glPushMatrix();
		glTranslatef(0, 0, walk);
		//glScalef(3.7, 3.7, 3.7);
		glPushMatrix();
			RobotHead();
			RobotBody();
			RobotLeftArm();
			RobotRightArm();
			RobotLeg();
			WeaponTrigger();
		glPopMatrix();
	glPopMatrix();
}

/*
 * --------------------------------------------------------------------
 *								Robot
 * --------------------------------------------------------------------
*/

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0.75, 0.79, 1);
	glEnable(GL_DEPTH_TEST);

	referenceLine();

	////	Transformation
	glRotatef(rSpeed, rx, ry, rz);
	robotDisplay();
}

/*
 * --------------------------------------------------------------------
 *								WinMain
 * --------------------------------------------------------------------
*/

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Lighting();
		//Projection();
		Display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------