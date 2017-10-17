#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include "physics.h"
#include "draw.h"
#include "player.h"
#include "objloader.h"

#define FPS 60

enum CAM_MODE {	C_KB=0,C_MOUSE};

using namespace std;

int keyState[300];
Camera cam;
bool light = true;
int width,height;

GLMmodel* build01;
GLMmodel* asphalt;
GLMmodel* walkway;
GLMmodel* torre;
GLMmodel* aura;
GLMmodel* main_body;
GLMmodel* main_window;
GLMmodel* main_insidewindow;
GLMmodel* main_ring;
GLMmodel* main_lateral;
GLMmodel* main_hall_generic;
GLMmodel* main_bot;
GLMmodel* main_elevator;
GLMmodel* main_groundlight;
GLMmodel* main_leaf;
GLMmodel* main_wood;
GLMmodel* main_vase;
GLMmodel* main_mesa;
GLMmodel* main_tapete;
GLMmodel* main_sofa;
GLMmodel* ground;
GLMmodel* cloud;

double increment = 0;

GLuint skybox_texture;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void init()
{
	glClearColor (0.4, 0.8, 1.0, 1.0);

	// Show/hide mouse
		glutSetCursor(GLUT_CURSOR_NONE);

	// Enable's
		// Enable Depth Test
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

		// Enable Color Material
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		// Enable blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Fog
	{
		float cor[] = { .5f, .7f, 0.9f };

		glFogi(GL_FOG_MODE, GL_LINEAR);        // Linear, exp. ou exp²
		glFogfv(GL_FOG_COLOR, cor);         // Cor
		glFogf(GL_FOG_DENSITY, 0.35f);      // Densidade
		glHint(GL_FOG_HINT, GL_DONT_CARE);  // Não aplicar se não puder
		glFogf(GL_FOG_START, 00.0f);         // Profundidade inicial
		glFogf(GL_FOG_END, 2000000.0f);           // Profundidade final
		glEnable(GL_FOG);                   // Liga GL_FOG
	}

	// Sun
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		{ // apenas para criar/limitar escopo de a/b/c/d/e (SIM, È POSSÍVEL, TBM N TO ACREDITANDO Q CHUTEI CERTO)
			GLfloat a[] = {.1,.1,.1,1};
			glLightfv(GL_LIGHT0,GL_AMBIENT,a);

			GLfloat b[] = {.5,.5,.5,1};
			glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

			GLfloat c[] = {0,0,0,1};
			glLightfv(GL_LIGHT0,GL_SPECULAR,c);

			GLfloat d[] = {0.5,1,0.866,0};
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


	// Carregar obj
		build01 = glmReadOBJ("models/city/build01.obj");
		glmFacetNormals(build01);
		glmVertexNormals(build01, 90.0);
		glmScale(build01, 10);

		walkway = glmReadOBJ("models/city/walkway.obj");
		glmFacetNormals(walkway);
		glmVertexNormals(walkway, 90.0);
		glmScale(walkway, 10);

		asphalt = glmReadOBJ("models/city/asphalt.obj");
		glmFacetNormals(asphalt);
		glmVertexNormals(asphalt, 90.0);
		glmScale(asphalt, 10);

		torre = glmReadOBJ("models/torre/torre.obj");
		glmFacetNormals(torre);
		glmVertexNormals(torre, 90.0);
		glmScale(torre, 20);

		aura = glmReadOBJ("models/torre/3daura.obj");
		glmFacetNormals(aura);
		glmVertexNormals(aura, 90.0);
		glmScale(aura, 15);

		main_body = glmReadOBJ("models/predio/main_body.obj");
		glmFacetNormals(main_body);
		glmVertexNormals(main_body, 90.0);
		glmScale(main_body, 10);

		main_window = glmReadOBJ("models/predio/main_window.obj");
		glmFacetNormals(main_window);
		glmVertexNormals(main_window, 90.0);
		glmScale(main_window, 10);

		main_insidewindow = glmReadOBJ("models/predio/main_insidewindow.obj");
		glmFacetNormals(main_insidewindow);
		glmVertexNormals(main_insidewindow, 90.0);
		glmScale(main_insidewindow, 10);

		main_ring = glmReadOBJ("models/predio/main_ring.obj");
		glmFacetNormals(main_ring);
		glmVertexNormals(main_ring, 90.0);
		glmScale(main_ring, 10);

		main_elevator = glmReadOBJ("models/predio/main_elevator.obj");
		glmFacetNormals(main_elevator);
		glmVertexNormals(main_elevator, 90.0);
		glmScale(main_elevator, 10);

		main_lateral = glmReadOBJ("models/predio/main_lateral.obj");
		glmFacetNormals(main_lateral);
		glmVertexNormals(main_lateral, 90.0);
		glmScale(main_lateral, 10);

		main_hall_generic = glmReadOBJ("models/predio/main_hall_generic.obj");
		glmFacetNormals(main_hall_generic);
		glmVertexNormals(main_hall_generic, 90.0);
		glmScale(main_hall_generic, 10);

		main_bot = glmReadOBJ("models/predio/main_bot.obj");
		glmFacetNormals(main_bot);
		glmVertexNormals(main_bot, 90.0);
		glmScale(main_bot, 10);

		main_groundlight = glmReadOBJ("models/predio/main_groundlight.obj");
		glmFacetNormals(main_groundlight);
		glmVertexNormals(main_groundlight, 90.0);
		glmScale(main_groundlight, 10);

		main_leaf = glmReadOBJ("models/predio/main_leaf.obj");
		glmFacetNormals(main_leaf);
		glmVertexNormals(main_leaf, 90.0);
		glmScale(main_leaf, 10);

		main_wood = glmReadOBJ("models/predio/main_wood.obj");
		glmFacetNormals(main_wood);
		glmVertexNormals(main_wood, 90.0);
		glmScale(main_wood, 10);

		main_vase = glmReadOBJ("models/predio/main_vase.obj");
		glmFacetNormals(main_vase);
		glmVertexNormals(main_vase, 90.0);
		glmScale(main_vase, 10);

		main_mesa = glmReadOBJ("models/predio/main_mesa.obj");
		glmFacetNormals(main_mesa);
		glmVertexNormals(main_mesa, 90.0);
		glmScale(main_mesa, 10);

		main_tapete = glmReadOBJ("models/predio/main_tapete.obj");
		glmFacetNormals(main_tapete);
		glmVertexNormals(main_tapete, 90.0);
		glmScale(main_tapete, 10);

		main_sofa = glmReadOBJ("models/predio/main_sofa.obj");
		glmFacetNormals(main_sofa);
		glmVertexNormals(main_sofa, 90.0);
		glmScale(main_sofa, 10);

		ground = glmReadOBJ("models/predio/ground.obj");
		glmFacetNormals(ground);
		glmVertexNormals(ground, 90.0);
		glmScale(ground, 10);

		cloud = glmReadOBJ("models/city/cloud.obj");
		glmFacetNormals(cloud);
		glmVertexNormals(cloud, 90.0);
		glmScale(cloud, 10);

}

void drawText(void* font, string str, double x, double y)
{
	glPushMatrix();

		glTranslatef(0,0,10);
		glScalef(100,100,100);
		glRasterPos2d(x,y);

		for(int i=0;i<str.size();i++)
		glutBitmapCharacter(font,str[i]);

	glPopMatrix();
}

void emissive(double alpha)
{
	GLfloat d[4] = {alpha,alpha,alpha,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d);
}

void draw_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
		gluLookAt(cam.eye.x+(cos((cam.bob/2)*M_PI/180)/50),cam.height+cam.eye.y+(sin(cam.bob*M_PI/180)/80),cam.eye.z,
					cam.eye.x+sin(cam.degree*M_PI/180),cam.height+cam.eye.y+sin(cam.vdegree*M_PI/180),cam.eye.z+cos(cam.degree*M_PI/180),
					0,1,0);

		/*// Skybox
			glColor4f(1,1,1,.5);
			drawSkybox(cam.eye.x,cam.eye.y,cam.eye.z,20000,skybox_texture);*/

		// Sun
		drawSun(increment);

		// Clouds
		glPushMatrix();
			emissive(.6);
				glRotatef(increment/60,0,1,0);
				glTranslatef(0,50000,0);
				glColor4f(1,1,1,.7);
				glScalef(1000,1000,1000);
				glmDraw(cloud,GLM_SMOOTH);
			emissive(0);
		glPopMatrix();

		// Cidade
			glColor4f(.5,.5,.5,1);
			drawModel(0,-10,500,180,0,build01,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.1,.1,.1,1);
			drawModel(0,-10,500,180,0,asphalt,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.2,.2,.2,1);
			drawModel(0,-10,500,180,0,walkway,GLM_FLAT | GLM_MATERIAL);

		// Desenhar prédio
			emissive(.2);
				glColor4f(.4,1,1,.5);
				drawModel(0,-10,500,180,0,main_insidewindow,GLM_FLAT | GLM_MATERIAL);
				drawModel(0,-10,500,180,0,main_window,GLM_FLAT | GLM_MATERIAL);
			emissive(0);
			glColor4f(.2,.2,.2,1);
			drawModel(0,-10,500,180,0,main_body,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.2,.2,.2,1);
			drawModel(0,-10,500,180,0,main_lateral,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.3,.3,.3,1);
			drawModel(0,-10,500,180,0,main_ring,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.5,.5,.5,1);
			drawModel(0,-10,500,180,0,main_elevator,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.2,.7,.8,1);
			drawModel(0,-10+sin(increment*M_PI/180),500,180,0,main_bot,GLM_FLAT | GLM_MATERIAL);
			glColor4f(1,1,1,1);
			drawModel(0,-10,500,180,0,main_groundlight,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.1,.7,.3,1);
			drawModel(0,-10,500,180,0,main_leaf,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.8,.4,.2,1);
			drawModel(0,-10,500,180,0,main_wood,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.6,.2,.1,1);
			drawModel(0,-10,500,180,0,main_vase,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.8,.7,.6,1);
			drawModel(0,-10,500,180,0,main_mesa,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.5,.5,.5,1);
			drawModel(0,-10,500,180,0,main_tapete,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.8,.8,.8,1);
			drawModel(0,-10,500,180,0,main_sofa,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.1,.1,.1,1);
			drawModel(0,-10,500,180,0,main_hall_generic,GLM_FLAT | GLM_MATERIAL);

		// Montanhas
			glColor4f(.2,.7,.1,1);
			drawModel(0,-10,500,180,0,ground,GLM_FLAT | GLM_MATERIAL);

		/*glColor4f(0,0,1,1);
		drawPlane(0,-10,750,1000);*/

		/*glColor4f(1,1,0,1);//(1,0,0,1);
		drawWireCube(0,0,-50,10);

		glColor4f(1,0.5,0.5,1);
		drawWireCube(50,0,0,10);

		glColor4f(1,1,0,1);
		drawWireCube(-50,0,0,10);

		glColor4f(1,0,1,1);
		drawWireCube(0,0,50,10);*/


		// OBS: o que precisa ser desenhado com transparencia precisa ser desenhado por último
		/*glColor4f(0,.5,1,.5);
		drawModel(0,30,400,increment,10,torre,GLM_FLAT | GLM_MATERIAL);
		glColor4f(0,.5,1,.1);
		drawModel(0,30,400,increment,10,aura,GLM_FLAT | GLM_MATERIAL);*/

	glPopMatrix();

	drawText(GLUT_BITMAP_HELVETICA_18,"ELEVADOR (E)",0,0);
	if(cam.display_text!="")
		glutWireCube(10);

	glutSwapBuffers();
}

void update_callback(int)
{
	calculatePhysics(keyState,cam);

	if(keyState['i'])
		increment+=20;

	increment+=2;

	// Sun/Moon
	{
		GLfloat a[] = {cos(.01*increment*M_PI/180)/10,cos(.01*increment*M_PI/180)/10,cos(.01*increment*M_PI/180)/10,1};
		glLightfv(GL_LIGHT0,GL_AMBIENT,a);

		GLfloat b[] = {.1+cos(.01*increment*M_PI/180)/5,.1+cos(.01*increment*M_PI/180)/5,.1+cos(.01*increment*M_PI/180)/5,1};
		glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

		// 0.4, 0.8, 1.0, 1.0
		double colorR = 0.2*cos(.01*increment*M_PI/180);
		double colorG = 0.8*cos(.01*increment*M_PI/180);
		double colorB = 1*cos(.01*increment*M_PI/180);
		if(colorB <= .1)
		{
			colorR=0;
			colorG=.05;
			colorB=.1;
		}
		glClearColor(colorR, colorG, colorB, 1.0);
	}

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

	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 10000000.0);
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

	if(key=='p')
		cout << "X(" << cam.eye.x << ") | Z(" << cam.eye.z << ")" << endl;

	if(key=='m' && cam.mode==C_MOUSE)
		cam.mode=C_KB;
	else if(key=='m')
		cam.mode=C_MOUSE;

	if(key=='j' && cam.eye.y==0)
		cam.vspd+=3;

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
