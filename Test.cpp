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
//struct Vector3
//{
//    float x, y, z;
//};
//
//struct ThirdPersonCamera_t
//{
//    struct Vector3 vecPos;
//    struct Vector3 vecRot;
//    float fRadius;			// Distance between the camera and the object.
//    float fLastX;
//    float fLastY;
//};
//
//struct ThirdPersonCamera_t camera;
//
//
//float distance(const struct Vector3* v1, const struct Vector3* v2)
//{
//    float d = 0.0f;
//    float x = v2->x - v1->x;
//    float y = v2->y - v1->y;
//    float z = v2->z - v1->z;
//
//    x *= x;
//    y *= y;
//    z *= z;
//
//    d = sqrt(x + y + z);
//
//    return d;
//}
//
//void calculate_distances(void)
//{
//    int i;
//    struct Vector3 neg_camera;
//
//    // In order to accurately calculate the distance between the spheres and 
//    // the camera, the x and z values should be converted to negatives, and
//    // the y coordinate should be ignored.  The camera updates the y value 
//    // still, but in a 3rd person shooter/adventure style game, the is calc-
//    // lations are done seperately from the camera to compensate for jumping
//    // and gravity, etc.
//    neg_camera.x = camera.vecPos.x * -1.0f;
//    neg_camera.y = 0.0f;
//    neg_camera.z = camera.vecPos.z * -1.0f;
//
//    //for (i = 0; i < sphere_count; i++)
//    //{
//    //    spheres[i].distance = distance(&neg_camera, &spheres[i].position);
//    //}
//}
//
//void draw_axes(void)
//{
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//    glDisable(GL_LIGHTING);
//    glEnable(GL_LINE_SMOOTH);
//
//    glPushMatrix();
//    glTranslatef(0.0f, 0.0f, 0.0f);
//
//    glBegin(GL_LINES);
//
//    // X Axis (Red)
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glVertex3f(0.0f, 0.0f, 0.0f);
//    glVertex3f(2.0f, 0.0f, 0.0f);
//
//    // Y Axis (Green)
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glVertex3f(0.0f, 0.0f, 0.0f);
//    glVertex3f(0.0f, 2.0f, 0.0f);
//
//    // Z Axis (Blue)
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glVertex3f(0.0f, 0.0f, 0.0f);
//    glVertex3f(0.0f, 0.0f, 2.0f);
//
//    glEnd();
//
//    glPopMatrix();
//
//    glPopAttrib();
//}
//
//void show_camera_stats(void)
//{
//    char string[128];
//
//    sprintf(string, "Camera <%f,%f,%f>", camera.vecPos.x, camera.vecPos.y, camera.vecPos.z);
//    //glPrintf(30, 30, GLUT_BITMAP_9_BY_15, string);
//}
//int glh_extension_supported(const char* extension)
//{
//    static const GLubyte* extensions = NULL;
//    const GLubyte* start;
//    GLubyte* where, * terminator;
//
//    // Extension names should not have spaces. 
//    where = (GLubyte*)strchr(extension, ' ');
//    if (where || *extension == '\0')
//        return 0;
//
//    if (!extensions)
//        extensions = glGetString(GL_EXTENSIONS);
//
//    // It takes a bit of care to be fool-proof about parsing the
//    // OpenGL extensions string.  Don't be fooled by sub-strings,
//    // etc.
//    start = extensions;
//    for (;;)
//    {
//        where = (GLubyte*)strstr((const char*)start, extension);
//        if (!where)
//            break;
//        terminator = where + strlen(extension);
//        if (where == start || *(where - 1) == ' ')
//        {
//            if (*terminator == ' ' || *terminator == '\0')
//            {
//                return 1;
//            }
//        }
//        start = terminator;
//    }
//    return 0;
//}
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

