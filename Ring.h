#ifdef WIN32 // For windows builds
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <gl\freeglut.h>

using namespace std;

extern GLfloat angle;

extern struct ThirdPersonCamera_t camera;

class Donut {

public:
	float x;
	float y;
	float z;
	bool bAnswer;
	bool bDraw;
	string txtAnswer;
	Donut();
	Donut(float x, float z, bool answer, bool draw, string txtAns, float y = 1.75);
};

void makeDonuts(float cameraX, float cameraZ);

bool donutOnDonut(int x, int z);

void hitDonut(float cameraX, float cameraZ);

void drawDonuts();