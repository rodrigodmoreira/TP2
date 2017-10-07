#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
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
bool light = true;
int width,height;

GLMmodel* city;
GLMmodel* torre;
GLMmodel* predio;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void init()
{
	glClearColor (0.4, 0.8, 1.0, 1.0);

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Fog
		/*float cor[] = { .3f, .6f, 0.7 };

		glFogi(GL_FOG_MODE, GL_LINEAR);        // Linear, exp. ou exp²
		glFogfv(GL_FOG_COLOR, cor);         // Cor
		glFogf(GL_FOG_DENSITY, 0.35f);      // Densidade
		glHint(GL_FOG_HINT, GL_DONT_CARE);  // Não aplicar se não puder
		glFogf(GL_FOG_START, 100.0f);         // Profundidade inicial
		glFogf(GL_FOG_END, 500.0f);           // Profundidade final
		glEnable(GL_FOG);                   // Liga GL_FOG
*/
	// Sun
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		{ // apenas para criar/limitar escopo de a/b/c/d/e (SIM, È POSSÍVEL, TBM N TO ACREDITANDO Q CHUTEI CERTO)
			GLfloat a[] = {.1,.1,.1,1};
			glLightfv(GL_LIGHT0,GL_AMBIENT,a);

			GLfloat b[] = {.4,.6,.8,1};
			glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

			GLfloat c[] = {125/255,125/255,125/255,1};
			glLightfv(GL_LIGHT0,GL_SPECULAR,c);

			GLfloat d[] = {300,300,300,1};
			glLightfv(GL_LIGHT0,GL_POSITION,d);

			GLfloat e[] = {3,3,3,1};
			glLightfv(GL_LIGHT0,GL_CONSTANT_ATTENUATION,e);
		} // Isso pq n encontrei uma forma bacana de reaproveitar o mesmo vetor atribuindo valores direto igual a {x1,x2,x3,x4}

	/*	glEnable(GL_LIGHT1);
		{ // apenas para criar/limitar escopo de a/b/c/d/e
			GLfloat a[] = {10/255,10/255,10/255,1};
			glLightfv(GL_LIGHT0,GL_AMBIENT,a);

			GLfloat b[] = {255/255,255/255,255/255,1};
			glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

			GLfloat c[] = {125/255,125/255,125/255,1};
			glLightfv(GL_LIGHT0,GL_SPECULAR,c);

			GLfloat d[] = {-300,-300,-300,0};
			glLightfv(GL_LIGHT0,GL_POSITION,d);

			GLfloat e[] = {1,1,1,1};
			//glLightfv(GL_LIGHT0,GL_CONSTANT_ATTENUATION,e);
		}*/


	city = glmReadOBJ("models/test/The City.obj");
	glmFacetNormals(city);
	glmVertexNormals(city, 90.0);
	glmScale(city, 1);

	torre = glmReadOBJ("models/torre/torre.obj");
	glmFacetNormals(torre);
	glmVertexNormals(torre, 90.0);
	glmScale(torre, 10);

	predio = glmReadOBJ("models/predio/predio.obj");
	glmFacetNormals(predio);
	glmVertexNormals(predio, 90.0);
	glmScale(predio, 10);	

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

		glColor4f(1,0,0,1);
		drawModel(0,-50,0,0,0,city,GLM_SMOOTH | GLM_MATERIAL);
	
		glColor4f(1,1,1,0.1);
		drawModel(0,-10,100,0,10,torre,GLM_SMOOTH | GLM_MATERIAL);

		glColor4f(1,1,0,1);
		drawModel(0,-10,-500,180,0,predio,GLM_SMOOTH | GLM_MATERIAL);

		glColor4f(0,0,1,1);
		drawPlane(0,-10,750,1000);

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
			cam.degree-=1.5*cam.mousesense;
		else if(x<cam.mlast.x)
			cam.degree+=1.5*cam.mousesense;

		if(y>cam.mlast.y && cam.vdegree<90)
			cam.vdegree+=cam.mousesense;
		else if(y<cam.mlast.y && cam.vdegree>-90)
			cam.vdegree-=cam.mousesense;	
	}

	cout << cam.vdegree << endl;

	cam.mlast.x=x;
	cam.mlast.y=y;

	if(x>=width-100 || x<=100 || y>=height-100 || y<=100)
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
