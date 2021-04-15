#ifdef WIN32 // For windows builds
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gl\glut.h>
#include <time.h>

struct Vector3
{
	float x, y, z;
};
struct ThirdPersonCamera_t
{
	struct Vector3 vecPos;
	struct Vector3 vecRot;
	float fRadius;			// Distance between the camera and the object.
	float fLastX;
	float fLastY;
	float fLastZ;
};

struct ThirdPersonCamera_t camera;
GLuint floor_tex = 0;
GLint hits = 0;
int object = 0;
float xmove[]{ 0, 0 };
float ymove[]{ 0, 0 };
float zmove[]{ 0, 0 };


void glEnable2D(void)
{
	GLint iViewport[4];

	glGetIntegerv(GL_VIEWPORT, iViewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(iViewport[0], iViewport[0] + iViewport[2], iViewport[1] + iViewport[3], iViewport[1], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}
void glDisable2D(void)
{
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
void glPrintf(int x, int y, void* font, char* string, ...)
{
	char* c;
	char temp[256];
	va_list ap;

	va_start(ap, string);
	vsprintf(temp, string, ap);
	va_end(ap);

	glEnable2D();

	glRasterPos2i(x, y);

	for (c = temp; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}

	glDisable2D();
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
void draw_crosshair(void)
{
	float fViewport[4];
	float w = 32.0f, h = 32.0f;
	glGetFloatv(GL_VIEWPORT, fViewport);
	glEnable2D();

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f((fViewport[2] / 2.0f) - (w / 2.0f), fViewport[3] / 2.0f);
	glVertex2f((fViewport[2] / 2.0f) + (w / 2.0f), fViewport[3] / 2.0f);
	glVertex2f(fViewport[2] / 2.0f, (fViewport[3] / 2.0f) - (h / 2.0f));
	glVertex2f(fViewport[2] / 2.0f, (fViewport[3] / 2.0f) + (h / 2.0f));
	glEnd();
	glDisable2D();
}
void show_camera_stats(void)
{
	char string[128];

	sprintf(string, "Camera <%f,%f,%f>", camera.vecPos.x, camera.vecPos.y, camera.vecPos.z);
	glPrintf(30, 30, GLUT_BITMAP_9_BY_15, string);
}
int glh_extension_supported(const char* extension)
{
	static const GLubyte* extensions = NULL;
	const GLubyte* start;
	GLubyte* where, * terminator;
	where = (GLubyte*)strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;

	if (!extensions)
		extensions = glGetString(GL_EXTENSIONS);
	start = extensions;
	for (;;)
	{
		where = (GLubyte*)strstr((const char*)start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
		{
			if (*terminator == ' ' || *terminator == '\0')
			{
				return 1;
			}
		}
		start = terminator;
	}
	return 0;
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
void DisplayFunction(void)
{
	int iViewport[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, -2.0f, -camera.fRadius);
	glRotatef(camera.vecRot.x, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidTetrahedron();

	glRotatef(camera.vecRot.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camera.vecPos.x, 0.0f, -camera.vecPos.z);
	glGetIntegerv(GL_VIEWPORT, iViewport);

	floor_render(50.0f, -0.75f);

	draw_crosshair();

	glColor3f(0.0f, 0.0f, 1.0f);
	show_camera_stats();
	glutSwapBuffers();
}


void IdleFunction(void)
{
	glutPostRedisplay();
}

void KeyboardFunction(GLubyte k, int x, int y)
{
	static float fRotSpeed = 5.0f;

	if ((GetKeyState(0x51) & 0x8000))
	{
		camera.vecRot.y -= fRotSpeed;
		if (camera.vecRot.y > 360) camera.vecRot.y -= 360;
	}
	if ((GetKeyState(0x45) & 0x8000))
	{
		camera.vecRot.y += fRotSpeed;
		if (camera.vecRot.y < -360) camera.vecRot.y += 360;
	}
	if ((GetKeyState(VK_SPACE) & 0x8000)) {
		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f);
		//camera.vecPos.x += (float)(sin(yrotrad));
		camera.vecPos.z += (float)(cos(yrotrad));
		//camera.vecPos.y += (float)(sin(xrotrad));
	}
	if ((GetKeyState(0x57) & 0x8000))
	{
		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f);
		camera.vecPos.x += (float)(sin(yrotrad));
		camera.vecPos.z -= (float)(cos(yrotrad));
		camera.vecPos.y -= (float)(sin(xrotrad));
	}
	if ((GetKeyState(0x53) & 0x8000))
	{
		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f);
		camera.vecPos.x -= (float)(sin(yrotrad));
		camera.vecPos.z += (float)(cos(yrotrad));
		camera.vecPos.y += (float)(sin(xrotrad));
	}
	if ((GetKeyState(0x44) & 0x8000))
	{
		float yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		camera.vecPos.x += (float)(cos(yrotrad)) * 0.5f;
		camera.vecPos.z += (float)(sin(yrotrad)) * 0.5f;
	}
	if ((GetKeyState(0x41) & 0x8000))
	{
		float yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		camera.vecPos.x -= (float)(cos(yrotrad)) * 0.5f;
		camera.vecPos.z -= (float)(sin(yrotrad)) * 0.5f;
	}

	// Has escape been pressed?
	if (k == 27)
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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(900, 900);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutCreateWindow("3D Game Go Burrrrrrrrrrrrrrrrrrrrrrrrrrr");
	InitScene();
	glutIdleFunc(IdleFunction);
	glutDisplayFunc(DisplayFunction);
	glutKeyboardFunc(KeyboardFunction);
	glutReshapeFunc(ReshapeFunction);
	glutMainLoop();

	return 0;
}