//#include <iostream>
//#ifdef WIN32 // For windows builds
//#include <windows.h>
//#endif
//#include <GL/glut.h>
//#include <stdlib.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <cmath>
//#include <stdio.h>
//#include <string>
//#include <map>
//#include <time.h>
//
//#include "Stars.h"
//
//
//#define FRAMES 30
//
//
//char title[] = "3D Shapes";
//GLfloat anglePyramid = 0.0f;
//int refreshMills = 15;
//int object = 0;
//float xmove[]{ 0, 0 };
//float ymove[]{ 0, 0 };
//float zmove[]{ 0, 0 };
//bool* keyStates = new bool[256];
//
//
//std::map< unsigned char, bool > state;
//bool keyDown[256];
//void framesCallback(int);
//void keyboardCallback_down(unsigned char, int, int);
//void keyboardCallback_up(unsigned char, int, int);
//
//void initGL() {
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
//	glClearDepth(5.0f); 
//	glEnable(GL_DEPTH_TEST); 
//	glDepthFunc(GL_LEQUAL);
//	glShadeModel(GL_SMOOTH);  
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
//}
//
//float degree = 10;
//float xscale = 0.08, yscale = 0.08, zscale = 0.08;
////
//void keyboardCallback_down(unsigned char key, int x, int y)
//{
//    std::cout << "Xmove"
//        << std::endl;
//    std::cout <<
//        xmove[object]
//        << std::endl;
//    std::cout << "Ymove"
//        << std::endl;
//    std::cout <<
//        ymove[object]
//        << std::endl;
//    keyStates[key] = true;
//
//    if ((GetKeyState(0x41) & 0x8000)) {
//        if (xmove[object] > -11.2)
//            xmove[object] -= 0.2;
//    }
//    if ((GetKeyState(0x44) & 0x8000)) {
//        if (xmove[object] < 11.2)
//            xmove[object] += 0.2;
//    }
//    if ((GetKeyState(0x53) & 0x8000)) {
//        if (ymove[object] > -15.4)
//        {
//            ymove[object] -= 0.2;
//            zmove[object] += 0.2;
//        }
//    }
//    if ((GetKeyState(0x57) & 0x8000)) {
//        if (ymove[object] < 16.4)
//        {
//            ymove[object] += 0.2;
//            zmove[object] -= 0.2;
//        }
//    }
//    glutPostRedisplay();
//}
//
//void keyboardCallback_up(unsigned char key, int x, int y) {
//    keyStates[key] = false;
//
//    if ((GetKeyState(0x41) & 0x8000)) {
//        if (xmove[object] > -11.2)
//            xmove[object] -= 0.2;
//    }
//    if ((GetKeyState(0x44) & 0x8000)) {
//        if (xmove[object] < 11.2)
//            xmove[object] += 0.2;
//    }
//    if ((GetKeyState(0x53) & 0x8000)) {
//        if (ymove[object] > -15.4)
//        {
//            ymove[object] -= 0.2;
//            zmove[object] += 0.2;
//        }
//    }
//    if ((GetKeyState(0x57) & 0x8000)) {
//        if (ymove[object] < 16.4)
//        {
//            ymove[object] += 0.2;
//            zmove[object] -= 0.2;
//        }
//    }
//    glutPostRedisplay();
//}
//
//
//
//void Settings()
//{
//    glClearColor(0, 0, 0, 0);
//    glClearDepth(5.0f);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glShadeModel(GL_SMOOTH);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//}
//
//
//void polygons(void)
//{
//
//    drawStars();
//
//    glDepthMask(GL_TRUE);
//    glEnable(GL_DEPTH_TEST);
//
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glPushMatrix();
//
//    glColor3f(1.0, 0.0, 0.0);
//    glRotatef(degree, 1.0, 0.0, 0.0);
//    glScalef(xscale, yscale, zscale);
//    glTranslatef(0, 0.0, 0.0);
//
//    glTranslatef(xmove[0], ymove[0], zmove[0]); // <--- translate pyramid
//
//
//    glBegin(GL_TRIANGLES);//pyramid
//    // fronat face
//    glColor3f(1.0f, 0.0f, 0.0f); //red
//    glVertex3f(0.0f, 1.0f, 0.0f);
//    glColor3f(0.0f, 1.0f, 0.0f); //green
//    glVertex3f(-1.0f, -1.0f, 1.0f);
//    glColor3f(0.0f, 0.0f, 1.0f); //blue
//    glVertex3f(1.0f, -1.0f, 1.0f);
//    // down face
//    glColor3f(1.0f, 0.0f, 0.0f); //red
//    glVertex3f(0.0f, 1.0f, 0.0f);
//    glColor3f(0.0f, 0.0f, 1.0f); //blue
//    glVertex3f(1.0f, -1.0f, 1.0f);
//    glColor3f(0.0f, 1.0f, 0.0f); //green
//    glVertex3f(1.0f, -1.0f, -1.0f);
//    //back
//    glColor3f(1.0f, 0.0f, 0.0f); //red
//    glVertex3f(0.0f, 1.0f, 0.0f);
//    glColor3f(0.0f, 1.0f, 0.0f); //green
//    glVertex3f(1.0f, -1.0f, -1.0f);
//    glColor3f(0.0f, 0.0f, 1.0f); //blue
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    //left 
//    glColor3f(1.0f, 0.0f, 0.0f); //reed
//    glVertex3f(0.0f, 1.0f, 0.0f);
//    glColor3f(0.0f, 0.0f, 1.0f); //blue
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glColor3f(0.0f, 1.0f, 0.0f); //green
//    glVertex3f(-1.0f, -1.0f, 1.0f);
//    glEnd();
//
//
//
//
//    glPopMatrix();
//    glPushMatrix();
//
//    glTranslatef(0, 0.0, 0);
// 
//    //glutSwapBuffers();
//}
//
//void DrawingFunction()//painting
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    polygons();
//    gluPerspective(10, 1, 2, 50.0);
//    glutSwapBuffers();
//}
//
//void AppearanceAdjustment(int x, int y)
//{
//    int aspect = x / y;
//    glViewport(0, 0, x, y);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//}
//
//void framesCallback(int) {
//
//    glutPostRedisplay();
//    glutTimerFunc(1000/FRAMES, framesCallback, 0);
//
//}
//
//int main(int argc, char** argv)
//{
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE);
//    glutInitWindowPosition(50, 50);
//    glutInitWindowSize(900, 900);
//    glutCreateWindow("3D Game go BURRRRRRRRRRRRRRRRRR");
//
//    
//
//    glutDisplayFunc(DrawingFunction);
//    glutTimerFunc(0, framesCallback, 0);
//    glutKeyboardFunc(keyboardCallback_down);
//    glutKeyboardUpFunc(keyboardCallback_up);
//    Settings();
//    glutMainLoop();
//    return 0;
//}
/*
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;

float cRadius = 10.0f;
float lastx, lasty;
float positionz[10];
float positionx[10];

void cubepositions(void) { //set the positions of the cubes

    for (int i = 0; i < 10; i++)
    {
        positionz[i] = rand() % 5 + 1;
        positionx[i] = rand() % 5 + 1;
    }
}

void cube(void) {
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] * 10);
        glutSolidCube(2);
        glPopMatrix();
    }
}

void init(void) {
    cubepositions();
}

void enable(void) {
    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_LIGHTING); //enable the lighting
    glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH); //set the shader to smooth shader

}

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //clear the color buffer and the depth buffer
    enable();

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -cRadius);
    glRotatef(xrot, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(2);

    glRotatef(yrot, 0.0, 1.0, 0.0);
    glTranslated(-xpos, 0.0f, -zpos);
    glColor3f(1.0f, 1.0f, 1.0f);
    cube();

    glutSwapBuffers();
    angle++;
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y) {
    if ((GetKeyState(0x51) & 0x8000))
    {
        xrot += 1;
        if (xrot > 360) {
            xrot -= 360;
        }
    }

    if ((GetKeyState(0x45) & 0x8000))
    {
        xrot -= 1;
        if (xrot < -360) xrot += 360;
    }

    if ((GetKeyState(0x53) & 0x8000))
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos += float(sin(yrotrad));
        zpos -= float(cos(yrotrad));
        ypos -= float(sin(xrotrad));
    }

    if ((GetKeyState(0x57) & 0x8000))
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos -= float(sin(yrotrad));
        zpos += float(cos(yrotrad));
        ypos += float(sin(xrotrad));
    }

    if ((GetKeyState(0x44) & 0x8000))
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos += float(cos(yrotrad)) * 0.2;
        zpos += float(sin(yrotrad)) * 0.2;
    }

    if ((GetKeyState(0x41) & 0x8000))
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos -= float(cos(yrotrad)) * 0.2;
        zpos -= float(sin(yrotrad)) * 0.2;
    }

    if (key == 27)
    {
        exit(0);
    }
}

void mouseMovement(int x, int y) {
    int diffx = x - lastx;
    int diffy = y - lasty;
    lastx = x;
    lasty = y;
    xrot += (float)diffy;
    yrot += (float)diffx;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Game Go BURRRRRRRRRRRRRRRR");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    //glutPassiveMotionFunc(mouseMovement);

    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
*/