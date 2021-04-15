#include <iostream>
#include <Windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <map>
//#include <GLFW/glfw3.h>

#define FRAMES 60


char title[] = "3D Shapes";
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]
int object = 0;
float xmove[]{ 0, 0 };
float ymove[]{ 0, 0 };
float zmove[]{ 0, 0 };

bool* keyStates = new bool[256];

std::map< unsigned char, bool > state;
bool keyDown[256];

void framesCallback(int);
void keyboardCallback_down(unsigned char, int, int);
void keyboardCallback_up(unsigned char, int, int);



void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

float degree = 10;
float xscale = 1, yscale = 1, zscale = 1;

void keyboardCallback_down(unsigned char key, int x, int y)
{
   /* switch (key)
    {
    case 'a': 
        xmove[object] -= 0.2;
        keyState[key] = 'a';
        state[key] = true;
        keyDown[key] = true;
        break;
    case 'd':
        xmove[object] += 0.2;
        keyState[key] = 'd';
        state[key] = true;
        keyDown[key] = true;
        break;
    case 's':
        ymove[object] -= 0.2;
        keyState[key] = 's';
        state[key] = true;
        keyDown[key] = true;
        break;
    case 'w':
        ymove[object] += 0.2;
        keyState[key] = 'w';
        state[key] = true;
        keyDown[key] = true;
        break;
    }*/

    keyStates[key] = true;

    if (key == 'a') {
        xmove[object] -= 0.2;
    }
    else if(key == 'd'){
        xmove[object] += 0.2;
    }
    else if (key == 's') {
        ymove[object] -= 0.2;
    }
    else if (key == 'w') {
        ymove[object] += 0.2;
    }
    
    glutPostRedisplay();
}

void keyboardCallback_up(unsigned char key, int x, int y) {
    keyStates[key] = false;

    if (key == 'a') {
        xmove[object] -= 0.2;
    }
    else if (key == 'd') {
        xmove[object] += 0.2;
    }
    else if (key == 's') {
        ymove[object] -= 0.2;
    }
    else if (key == 'w') {
        ymove[object] += 0.2;
    }


    glutPostRedisplay();
}



void Settings()
{
    glClearColor(1, 1, 1, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void polygons(void)
{
    glPushMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glRotatef(degree, 0.0, 1.0, 0.0);
    glScalef(xscale, yscale, zscale);
    glTranslatef(1.5, 0.0, -8.0);

    glTranslatef(xmove[0], ymove[0], zmove[0]); // <--- translate pyramid

    glBegin(GL_TRIANGLES);//pyramid
    // fronat face
    glColor3f(1.0f, 0.0f, 0.0f); //red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); //green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    // down face
    glColor3f(1.0f, 0.0f, 0.0f); //red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); //green
    glVertex3f(1.0f, -1.0f, -1.0f);
    //back
    glColor3f(1.0f, 0.0f, 0.0f); //red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); //green
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    glVertex3f(-1.0f, -1.0f, -1.0f);
    //left 
    glColor3f(1.0f, 0.0f, 0.0f); //reed
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); //green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glPopMatrix();
    glPushMatrix();


    glTranslatef(-1.5, 0.0, -8.0);

}

void DrawingFunction()//painting
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    polygons();
    glutSwapBuffers();
}

void AppearanceAdjustment(int x, int y)
{
    int aspect = x / y;
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, aspect, 1, 20);
}

void framesCallback(int) {

    glutPostRedisplay();
    glutTimerFunc(FRAMES, framesCallback, 0);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3d shapes");
    glutDisplayFunc(DrawingFunction);
    glutReshapeFunc(AppearanceAdjustment);
    glutKeyboardFunc(keyboardCallback_down);
    glutKeyboardUpFunc(keyboardCallback_up);
    Settings();
    glutMainLoop();
    return 0;
}