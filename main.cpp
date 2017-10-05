#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <cmath>
#include "physics.h"
#include "draw.h"
#include "player.h"
#include "objloader.h"

#define FPS 60

enum CAM_MODE { C_KB=0,C_MOUSE};

using namespace std;

int keyState[300];
Camera cam;
GLMmodel* city;
bool light = true;
int width,height;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void init()
{
	glClearColor (1.0, 1.0, 1.0, 1.0);

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Sun
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat a[] = {94.0/255,80.0/255,152.0/255,1};
		glLightfv(GL_LIGHT0,GL_AMBIENT,a);

		GLfloat b[] = {255/255,255/255,255/255,1};
		glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

		GLfloat c[4] = {125/255,125/255,125/255,1};
		glLightfv(GL_LIGHT0,GL_SPECULAR,c);

		GLfloat d[4] = {300,300,300,1};
		glLightfv(GL_LIGHT0,GL_POSITION,d);

		GLfloat e[4] = {5,5,5,1};
		glLightfv(GL_LIGHT0,GL_CONSTANT_ATTENUATION,e);

	city = glmReadOBJ("models/test/The City.obj");
	glmFacetNormals(city);
	glmVertexNormals(city, 90.0);
	glmScale(city, 1);
}

void materialGenerico()
{
	GLfloat a[] = {47.0/255,40.0/255,76.0/255,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,a);
	GLfloat b[] = {255/255,255/255,255/255,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,b);
	GLfloat c[4] = {125/255,125/255,125/255,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,c);
	GLfloat d[4] = {5/255,5/255,5/255,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d);
	GLfloat e[4] = {1/255,1/255,1/255,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,e);
}

void draw_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		gluLookAt(cam.eye.x+(cos((cam.bob/2)*M_PI/180)/50),cam.eye.y+(sin(cam.bob*M_PI/180)/80),cam.eye.z,
					cam.eye.x+sin(cam.degree*M_PI/180),cam.eye.y+sin(cam.vdegree*M_PI/180),cam.eye.z+cos(cam.degree*M_PI/180),
					0,1,0);

		//materialGenerico();

		glColor4f(0.5,0.5,0.5,1);
		drawModel(0,-50,0,city,GL_SMOOTH | GLM_MATERIAL);

		glColor4f(0,0,1,1);
		drawPlane(0,-5,0,100);

		glColor4f(1,1,0,1);//(1,0,0,1);
		drawWireCube(0,0,-50,10);

		glColor4f(1,0.5,0.5,1);
		drawWireCube(50,0,0,10);

		glColor4f(1,1,0,1);
		drawWireCube(-50,0,0,10);

		glColor4f(1,0,1,1);
		drawWireCube(0,0,50,10);
	glPopMatrix();

	glutSwapBuffers();
}

void update_callback(int)
{
	calculatePhysics(keyState,cam);

	glutPostRedisplay();

	glutTimerFunc(((double)1000)/FPS,update_callback,0); 
}

void reshape_callback(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	width=w;
	height=h;

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 10000.0);
	//glOrtho(0, w, 0, h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
}

void keyPress_callback(unsigned char key, int x, int y)
{
	if(key==27) exit(0);

	if(key=='l' && light)
	{
		glDisable(GL_LIGHTING);
		light=false;
	}
	else if(key=='l')
	{
		glEnable(GL_LIGHTING);
		light=true;
	}

	if(key=='m' && cam.mode==C_MOUSE)
		cam.mode=C_KB;
	else if(key=='m')
		cam.mode=C_MOUSE;
	
	keyState[(int)key]=1;
}

void keyRelease_callback(unsigned char key, int x, int y)
{
	keyState[(int)key]=0;
}

void passivemouse_callback(int x, int y)
{
	y=-y+768;

	if(cam.mode==C_MOUSE)
	{	
		if(x>cam.mlast.x)
			cam.degree-=cam.mousesense;
		else if(x<cam.mlast.x)
			cam.degree+=cam.mousesense;

		if(y>cam.mlast.y)
			cam.vdegree+=cam.mousesense;
		else if(y<cam.mlast.y)
			cam.vdegree-=cam.mousesense;
	}

	cam.mlast.x=x;
	cam.mlast.y=y;

	if(x>=width-5 || x<=1 || y>=height || y<=0)
		glutWarpPointer(1366.0/2,768/2);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glutInitContextVersion(1,1);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1366, 768);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("TP2");
	glutFullScreen();
	init();

	glutDisplayFunc(draw_callback);
	glutReshapeFunc(reshape_callback);
	glutKeyboardFunc(keyPress_callback);
	glutKeyboardUpFunc(keyRelease_callback);
	glutPassiveMotionFunc(passivemouse_callback);
	glutTimerFunc(0,update_callback,0);

	glutMainLoop();
	return 0;
}
