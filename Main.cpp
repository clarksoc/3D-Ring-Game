#ifdef WIN32 // For windows builds
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glm/glm.hpp>
#include <gl\glut.h>
#include <time.h>
#include <iostream>

#include "Stars.h"
#include "Ring.h"

using namespace std;

struct Vector3
{
	float x, y, z;
};
struct ThirdPersonCamera_t
{
	struct Vector3 vecPos;
	struct Vector3 vecRot;
	float fRadius;			
	float fLastX;
	float fLastY;
	float fLastZ;
};

struct ThirdPersonCamera_t camera;
GLuint floor_tex = 0;
GLfloat angle = 45.0f;
int refreshMill = 1;
bool startScreen = true;
int score = 0;
int speed = 1000;
bool showStartText = true;
bool showScore = false;
bool gameOver = false;
extern string question;

void chooseScreenCallback();
void startScreenCallback();
void gameOverScreenCallback();

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMill, timer, 0);
}
void showTextTimer(int value) {
	glutPostRedisplay();
	glutTimerFunc(5000, timer, 0);
	showStartText = false;
	showScore = true;
}

float distance(const struct Vector3* v1, const struct Vector3* v2)
{
	float d = 0.0f;
	float x = v2->x - v1->x;
	float y = v2->y - v1->y;
	float z = v2->z - v1->z;

	x *= x;
	y *= y;
	z *= z;

	d = sqrt(x + y + z);

	return d;
}

void texture_create(void)
{
	GLubyte buffer[64][64][4];
	int s, t;

	for (t = 0; t < 64; t++)
	{
		for (s = 0; s < 64; s++)
		{
			GLubyte c = ((((t & 0x8) == 0) ^ ((s & 0x8)) == 0)) * 255;
			buffer[s][t][0] = c;
			buffer[s][t][1] = c;
			buffer[s][t][2] = c;
			buffer[s][t][3] = 255;
		}
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &floor_tex);
	glBindTexture(GL_TEXTURE_2D, floor_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
void floor_render(float size, float y)
{

	size = 50;

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glPushMatrix();

	glTranslatef(0.0f, y, 0.0f);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floor_tex);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3f(-size, y, -size);
	glTexCoord2f(0.0f, 1.0f);		glVertex3f(-size, y, +size);
	glTexCoord2f(1.0f, 1.0f);		glVertex3f(+size, y, +size);
	glTexCoord2f(1.0f, 0.0f);		glVertex3f(+size, y, -size);
	glEnd();

	glPopMatrix();

	glPopAttrib();
}
int InitScene(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_DITHER);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	texture_create();

	memset(&camera, 0, sizeof(struct ThirdPersonCamera_t));
	camera.fRadius = 10.0f;
	srand(time(NULL));

	return GL_TRUE;
}


void startScreenCallback(void) {

	int iViewport[4];


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, -2.0f, -camera.fRadius);
	glRotatef(camera.vecRot.x + 0.1f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(1.0f, 32, 32);

	glRotatef(camera.vecRot.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camera.vecPos.x, -camera.vecPos.y, -camera.vecPos.z);
	glGetIntegerv(GL_VIEWPORT, iViewport);

	floor_render(50.0f, -0.75f);

	glColor3f(0.0f, 0.0f, 1.0f);
	const unsigned char* welcomeMessage = (const unsigned char*)("Welcome to 3D Game Go Burrrrrr \nUse W A S D to move Sanic through the answer rings \nAnswer questions correctly to earn points! \n\n Press Space to Start the Game!!!");

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(-1.0, 5.0, 0.0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, welcomeMessage);
	glPopMatrix();
	glutTimerFunc(10000, showTextTimer, 0);
	//makeDonuts(camera.vecPos.x, camera.vecPos.z);
	glutSwapBuffers();

}

void gameStateFunction(void)
{
	int iViewport[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	glTranslatef(0.0f, -2.0f, -camera.fRadius);
	glRotatef(camera.vecRot.x + 0.1f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(1.0f, 32, 32);


	glRotatef(camera.vecRot.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camera.vecPos.x, -camera.vecPos.y, -camera.vecPos.z);
	glGetIntegerv(GL_VIEWPORT, iViewport);

	floor_render(50.0f, -0.75f);

	hitDonut(camera.vecPos.x, camera.vecPos.z);
	drawDonuts();
	glColor3f(0.0f, 0.0f, 1.0f);

	char _score[10] = { 0 };

	_itoa_s(score, _score, 10);

	char messageInGame[50] = "Score: ";
	strcat_s(messageInGame, _score);

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(camera.vecPos.x + 1.0f, camera.vecPos.y + 1.0f, camera.vecPos.z + 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(messageInGame));

	glRasterPos3f(camera.vecPos.x - 1.0f, camera.vecPos.y + 2.0f, camera.vecPos.z + 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)question.c_str());

	if (gameOver) {
		glutDisplayFunc(gameOverScreenCallback);
	}

	glutSwapBuffers();
	angle += 1.0f;
}

void gameOverScreenCallback(void) {

	int iViewport[4];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, -2.0f, -camera.fRadius);
	glRotatef(camera.vecRot.x + 0.1f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(1.0f, 32, 32);

	glRotatef(camera.vecRot.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camera.vecPos.x, -camera.vecPos.y, -camera.vecPos.z);
	glGetIntegerv(GL_VIEWPORT, iViewport);

	floor_render(50.0f, -0.75f);

	glColor3f(0.0f, 0.0f, 1.0f);


	char finalScore[10] = { 0 };
	string endGameMessage;
	string pressR = "\nPress R to play again!";
	string outOf = "/25";


	_itoa_s(score, finalScore, 10);

	if (score < 10) {

		endGameMessage = "You need to work on your math skills! \nYour Final Score was: ";

	}
	else if (score < 25) {

		endGameMessage = "That was pretty good! \nYour Final Score was: ";

	}
	else {
		endGameMessage = "Perfect Score! \nYour Final Score was: ";
	}

	endGameMessage = endGameMessage + std::to_string(score) + outOf + pressR;

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(-1.0, 5.0, 0.0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)endGameMessage.c_str());
	glPopMatrix();
	glutTimerFunc(10000, showTextTimer, 0);

	glutSwapBuffers();

}

void resetGameState() {
	gameOver = false;
	startScreen = true;
	score = 0;
	chooseScreenCallback();
}

void MouseFunction(int x, int y)
{

	int diffx = x - camera.fLastX;
	int diffy = y - camera.fLastY;

	camera.fLastX = x;
	camera.fLastY = y;
	
	camera.vecRot.x += (float)diffy;
	camera.vecRot.y += (float)diffx;
	if (camera.vecRot.x < -10.0f)
		camera.vecRot.x = -10.0f;
	if (camera.vecRot.x > 30.0f)
		camera.vecRot.x = 30.0f;
}

void KeyboardFunction(GLubyte k, int x, int y)
{
	static float fRotSpeed = 5.0f;

	if ((GetKeyState(0x51) & 0x8000)) //Q
	{
		camera.vecRot.y -= fRotSpeed;
		if (camera.vecRot.y > 360) camera.vecRot.y -= 360;
	}
	if ((GetKeyState(0x45) & 0x8000)) //E
	{
		camera.vecRot.y += fRotSpeed;
		if (camera.vecRot.y < -360) camera.vecRot.y += 360;
	}
	if ((GetKeyState(0x30) & 0x8000))//0
	{
		camera.vecRot.x += fRotSpeed;
		if (camera.vecRot.x > 360) camera.vecRot.x -= 360;
	}
	if ((GetKeyState(0x31) & 0x8000))//1
	{
		camera.vecRot.x -= 1;
		if (camera.vecRot.x < -360) camera.vecRot.x += 360;
	}
	if ((GetKeyState(0x52) & 0x8000))//R
	{
		//TODO: Reset everything
		resetGameState();
	}
	if ((GetKeyState(VK_SPACE) & 0x8000)) { //SPACE
		startScreen = false;
		chooseScreenCallback();
		

	}
	if ((GetKeyState(0x58) & 0x8000)) { //X

		cout << "Zoom zoom down" << endl;
		cout <<camera.vecPos.y << endl;
		if(camera.vecPos.y >= 0)
			camera.vecPos.y -= 1;
	}

	if ((GetKeyState(0x57) & 0x8000)) //W
	{

		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f);

		if (camera.vecPos.y > -0.5 && camera.vecPos.y < 3 && camera.vecPos.x > -50 && camera.vecPos.x < 50
			&& camera.vecPos.z > -50 && camera.vecPos.z < 50) {
			camera.vecPos.x += (float)(sin(yrotrad)) * 1;
			camera.vecPos.z -= (float)(cos(yrotrad)) * 1;
			camera.vecPos.y -= (float)(sin(xrotrad)) * 1;
		}
		if (camera.vecPos.y <= -0.5) {
			camera.vecPos.y += 0.5;
		}
		if (camera.vecPos.y >= 3) {
			camera.vecPos.y -= 0.5;
		}
		if (camera.vecPos.x <= -50) {
			camera.vecPos.x += 0.5;
		}
		if (camera.vecPos.x >= 50) {
			camera.vecPos.x -= 0.5;
		}
		if (camera.vecPos.z <= -50) {
			camera.vecPos.z += 0.5;
		}
		if (camera.vecPos.z >= 50) {
			camera.vecPos.z -= 0.5;
		}



	}
	if ((GetKeyState(0x53) & 0x8000))// S
	{
		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f);

		if (camera.vecPos.y > -0.5 && camera.vecPos.y < 3 && camera.vecPos.x > -50 && camera.vecPos.x < 50
			&& camera.vecPos.z > -50 && camera.vecPos.z < 50) {
			camera.vecPos.x -= (float)(sin(yrotrad));
			camera.vecPos.z += (float)(cos(yrotrad));
			camera.vecPos.y += (float)(sin(xrotrad));
		}

		if (camera.vecPos.y <= -0.5) {
			camera.vecPos.y += 0.5;
		}
		if (camera.vecPos.y >= 3) {
			camera.vecPos.y -= 0.5;
		}
		if (camera.vecPos.x <= -50) {
			camera.vecPos.x += 0.5;
		}
		if (camera.vecPos.x >= 50) {
			camera.vecPos.x -= 0.5;
		}
		if (camera.vecPos.z <= -50) {
			camera.vecPos.z += 0.5;
		}
		if (camera.vecPos.z >= 50) {
			camera.vecPos.z -= 0.5;
		}
	}
	if ((GetKeyState(0x44) & 0x8000)) // D
	{
		float yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		if (camera.vecPos.y > -0.5 && camera.vecPos.y < 3 && camera.vecPos.x > -50 && camera.vecPos.x < 50
			&& camera.vecPos.z > -50 && camera.vecPos.z < 50) {
			camera.vecPos.x += (float)(cos(yrotrad)) * 0.5f;
			camera.vecPos.z += (float)(sin(yrotrad)) * 0.5f;
		}

		if (camera.vecPos.y <= -0.5) {
			camera.vecPos.y += 0.5;
		}
		if (camera.vecPos.y >= 3) {
			camera.vecPos.y -= 0.5;
		}
		if (camera.vecPos.x <= -50) {
			camera.vecPos.x += 0.5;
		}
		if (camera.vecPos.x >= 50) {
			camera.vecPos.x -= 0.5;
		}
		if (camera.vecPos.z <= -50) {
			camera.vecPos.z += 0.5;
		}
		if (camera.vecPos.z >= 50) {
			camera.vecPos.z -= 0.5;
		}
	}
	if ((GetKeyState(0x41) & 0x8000)) // A
	{
		float yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);

		if (camera.vecPos.y > -0.5 && camera.vecPos.y < 3 && camera.vecPos.x > -50 && camera.vecPos.x < 50
			&& camera.vecPos.z > -50 && camera.vecPos.z < 50) {
			camera.vecPos.x -= (float)(cos(yrotrad)) * 0.5f;
			camera.vecPos.z -= (float)(sin(yrotrad)) * 0.5f;
		}

		if (camera.vecPos.y <= -0.5) {
			camera.vecPos.y += 0.5;
		}
		if (camera.vecPos.y >= 3) {
			camera.vecPos.y -= 0.5;
		}
		if (camera.vecPos.x <= -50) {
			camera.vecPos.x += 0.5;
		}
		if (camera.vecPos.x >= 50) {
			camera.vecPos.x -= 0.5;
		}
		if (camera.vecPos.z <= -50) {
			camera.vecPos.z += 0.5;
		}
		if (camera.vecPos.z >= 50) {
			camera.vecPos.z -= 0.5;
		}
	}

	if ((GetKeyState(VK_ESCAPE) & 0x8000))// ESC
	{
		exit(0);
	}

	glutPostRedisplay();
}

void ReshapeFunction(GLsizei width, GLsizei height)
{
	if (!height) height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLdouble)width / height, 0.1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void chooseScreenCallback() {
	if (startScreen) {
		glutDisplayFunc(startScreenCallback);
		makeDonuts(camera.vecPos.x, camera.vecPos.z);
	}
	else {
		glutDisplayFunc(gameStateFunction);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(900, 900);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutCreateWindow("3D Game Go Burrrrrrrrrrrrrrrrrrrrrrrrrrr");
	InitScene();
	chooseScreenCallback();
	glutKeyboardFunc(KeyboardFunction);
	glutPassiveMotionFunc(MouseFunction);
	glutReshapeFunc(ReshapeFunction);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

	return 0;
}
