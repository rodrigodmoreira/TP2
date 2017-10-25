#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include "physics.h"
#include "draw.h"
#include "player.h"
#include "objloader.h"
#include "audio.h"

#define FPS 60

enum CAM_MODE {	C_KB=0,C_MOUSE};

using namespace std;

// ALthings
	enum AUDIO_BUFFER {AB_DOOR_OPEN=0, AB_ELEVATOR_RING, AB_8BITRAVE};
	enum AUDIO_SOURCE {AS_DEFAULT=0};

	// Buffers to hold sound data.
	ALuint al_buffer[100];

	// Sources are points of emitting sound.
	ALuint al_source[100];

	// Position of the source sound.
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	 
	// Velocity of the source sound.
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
	 
	// Position of the Listener.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
	 
	// Velocity of the Listener.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	 
	// Orientation of the Listener. (first 3 elements are "at", second 3 are "up") (vulgo "target" e vetor para cima)
	// Also note that these should be units of '1'.
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

// Some globals
	int keyState[300];
	Camera cam;
	bool light = true;
	int width,height;

// GLMmodels
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
	GLMmodel* main_hdoor;
	GLMmodel* ap_white;
	GLMmodel* ground;
	GLMmodel* cloud;
	GLMmodel* poste;
	GLMmodel* sLamp;
	GLMmodel* plane;

// Variavel "parametrica" correspondente ao tempo passado (utilizado pra fazer algumas coisas se moverem com o passar do tempo)
	double increment = 0;

// Posições de alguns objetos que se movem
	enum POSICOES{RHALLDOOR=0,LHALLDOOR,PLANE};
	Ponto p[100];

// Extrator de sinal - Guardando aqui para futuras referencias(código lindão)
	template <typename T> int sgn(T val) {
	    return (T(0) < val) - (val < T(0));
	}

void initAL()
{
	// Initialize OpenAL and clear the error bit. 
		alutInit(NULL, 0);
		alGetError();

	// Definir atenuação do som	
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

	// Load .wav (16 bit-only && mono)
		if(loadALData(al_buffer[AB_8BITRAVE],"sounds/Panda Eyes - Fake Princess.wav") == AL_FALSE)
		{
			printf("buffer_fudeo\n");
			exit(0);
		}

	// Bind audio to a source
		if(bindALData(al_buffer[AB_8BITRAVE],al_source[AS_DEFAULT], SourcePos, SourceVel, AL_TRUE) == AL_FALSE)
		{
			printf("source_fudeo\n");
			exit(0);
		}

	// Configure Listener initial values
		setListenerValues(ListenerPos,ListenerVel,ListenerOri);

	// Play audio on source
		alSourcePlay(al_source[AS_DEFAULT]);

	// Halt audio
		// alSourcePause(Source);

	// Stop audio
		// alSourceStop(Source);
}

void initPos()
{
	p[RHALLDOOR].set(25,0,-1,1);
	p[LHALLDOOR].set(0,0,0,1);
	p[PLANE].set(-1000,5000,15000,1);
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

			GLfloat e[] = {0,0,0,1};
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

		main_hdoor = glmReadOBJ("models/predio/main_rhdoor.obj");
		glmFacetNormals(main_hdoor);
		glmVertexNormals(main_hdoor, 90.0);
		glmScale(main_hdoor, 10);

		ap_white = glmReadOBJ("models/predio/ap_white.obj");
		glmFacetNormals(ap_white);
		glmVertexNormals(ap_white, 90.0);
		glmScale(ap_white, 10);

		ground = glmReadOBJ("models/predio/ground.obj");
		glmFacetNormals(ground);
		glmVertexNormals(ground, 90.0);
		glmScale(ground, 10);

		cloud = glmReadOBJ("models/city/cloud.obj");
		glmFacetNormals(cloud);
		glmVertexNormals(cloud, 90.0);
		glmScale(cloud, 10);

		poste = glmReadOBJ("models/city/poste.obj");
		glmFacetNormals(poste);
		glmVertexNormals(poste, 90.0);
		glmScale(poste, 10);

		sLamp = glmReadOBJ("models/city/streetLamp.obj");
		glmFacetNormals(sLamp);
		glmVertexNormals(sLamp, 90.0);
		glmScale(sLamp, 10);

		plane = glmReadOBJ("models/city/plane.obj");
		glmFacetNormals(plane);
		glmVertexNormals(plane, 90.0);
		glmScale(plane, 40);

		initPos();

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

	//	Criar lista para guardar desenho
	//	Resolve problema de objetos piscando na tela
	GLuint lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);	// Abre nova lista para compilar (guardar)
	
	glPushMatrix();
		gluLookAt(cam.eye.x+(cos((cam.bob/2)*M_PI/180)/50),cam.ground+cam.height+cam.eye.y+(sin(cam.bob*M_PI/180)/80),cam.eye.z,
					cam.eye.x+sin(cam.degree*M_PI/180),cam.ground+cam.height+cam.eye.y+sin(cam.vdegree*M_PI/180),cam.eye.z+cos(cam.degree*M_PI/180),
					0,1,0);

		// Sun
			drawSun(1*increment);

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
			glColor4f(1,1,1,1);
			drawModel(0,-10,500,180,0,build01,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.3,.3,.3,1);
			drawModel(0,-10,500,180,0,asphalt,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.4,.4,.4,1);
			drawModel(0,-10,500,180,0,walkway,GLM_FLAT | GLM_MATERIAL);
			glPushMatrix();
				glScalef(1,2,1);
				glColor4f(1,1,1,1);
				drawModel(0,-10,500,180,0,poste,GLM_FLAT | GLM_MATERIAL);
			glPopMatrix();
			glColor4f(1,1,1,1);
			drawModel(0+p[PLANE].x,-10+p[PLANE].y,500+p[PLANE].z,180,0,plane,GLM_FLAT | GLM_MATERIAL);

		// Apartamento
			glColor4f(1,1,1,.5);
			drawModel(0,-10,500,180,0,ap_white,GLM_FLAT | GLM_MATERIAL);

		// Prédio
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
			glColor4f(1,1,1,1);
			drawModel(0,-10,500,180,0,main_sofa,GLM_FLAT | GLM_MATERIAL);
			glColor4f(.95,.13,.19,1);
			drawModel(0,-10,500,180,0,main_hall_generic,GLM_FLAT | GLM_MATERIAL);
			emissive(.2);
				glColor4f(.4,1,1,.5);
				drawModel(0+(p[LHALLDOOR]).x,-10+(p[LHALLDOOR]).y,500+(p[LHALLDOOR]).z,180,0,main_hdoor,GLM_FLAT | GLM_MATERIAL);
				drawModel(0+(p[RHALLDOOR]).x,-10+(p[RHALLDOOR]).y,500+(p[RHALLDOOR]).z,180,0,main_hdoor,GLM_FLAT | GLM_MATERIAL);
			emissive(0);

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
		drawModel(0,30,400,increment,10,aura,GLM_FLAT | GLM_MATERIAL);*/// City
		glPushMatrix();
			glScalef(1,2,1);	
			emissive(.4);
				glColor4f(.7,.6,.5,.3);
				drawModel(0,-10,500,180,0,sLamp,GLM_FLAT | GLM_MATERIAL);
		glPopMatrix();

	glPopMatrix();


	// Mudar Projeção
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

		//gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 10000000.0);
		glOrtho(0, width, 0, height, -1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);

	drawText(GLUT_BITMAP_HELVETICA_18,"ELEVADOR (E)",0,0);
	if(cam.display_text!="")
		glutWireCube(10);

	// Retornar
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

		gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 10000000.0);
		//glOrtho(0, w, 0, h, -1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);

	glEndList();	// Fecha lista de desenho
	glCallList(lista);	// Envia a lista pronta para ser desenhada
	glDeleteLists(lista, 1);	// Deleta a lista usada
	
	glutSwapBuffers();
}

void update_callback(int)
{
	increment+=2;

	calculatePhysics(keyState,cam,p,increment);

	// Atualizar posição do ouvinte
	{		
		ALfloat lpos[] = {-cam.eye.x,-cam.eye.y,-cam.eye.z};
		ALfloat lvel[] = {cam.spd*sin(cam.degree*M_PI/180)*cam.hspd,0,cam.spd*cos(cam.degree*M_PI/180)*cam.hspd};
		ALfloat lori[] = {cam.eye.x+sin(cam.degree*M_PI/180),cam.ground+cam.height+cam.eye.y+sin(cam.vdegree*M_PI/180),cam.eye.z+cos(cam.degree*M_PI/180),
							0,1,0}; // Mesma coisa do gluLookAt (target + vetor vertical)
		//alSourcefv(al_source[AS_DEFAULT], AL_POSITION, lpos);
		setListenerValues(lpos,lvel,lori);
	}

	if(keyState['i'])
		increment+=20;

	glutTimerFunc(((double)1000)/FPS,update_callback,0); 
}

void idle_callback()	// MAX FPS BRO!!
{
	glutPostRedisplay();
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
	// ESC - Sair
	if(key==27) exit(0);

	// l - ON/OFF modelo de iluminação
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

	// Imprime posição da camera no terminal
	if(key=='p')
	{
		cout << "X(" << cam.eye.x << ") | Z(" << cam.eye.z << ")" << endl;
		cout << "Y(" << cam.eye.y << ")" << endl;
		printf("Y(%lf) | ground(%lf) | som(%lf)\n",cam.eye.y,(double)cam.ground,(double)(cam.ground+cam.vspd));
	}

	// Modo da camera (MOUSE+KB || KB_ONLY->DOOOOM)
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
	// Inverte e translada origem do sistema pra baixo
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
		glutWarpPointer(width/2,height/2);
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
	// glutFullScreen();

	init();
	initAL();

	glutDisplayFunc(draw_callback);
	glutReshapeFunc(reshape_callback);
	glutKeyboardFunc(keyPress_callback);
	glutKeyboardUpFunc(keyRelease_callback);
	glutPassiveMotionFunc(passivemouse_callback);
	glutTimerFunc(0,update_callback,0);
	glutIdleFunc(idle_callback);

	glutMainLoop();
	return 0;
}
