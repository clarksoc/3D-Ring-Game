#include <iostream>
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>

#include "StartScreen.h"


void RenderString(int x, int y, void* font, const unsigned char* string) {

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x, y);
	glutBitmapString(font, string);

}

