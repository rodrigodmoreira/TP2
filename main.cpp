#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <stdio.h>
#include <cstdlib> 
#include <iostream>
#include <cmath>
#include <string>
#include "physics.h"
#include "draw.h"
#include "player.h"
#include "objloader.h"
#include "audio.h"

#define FPS 120
#define NUM_ESTRELAS 1000

enum CAM_MODE {	C_KB=0,C_MOUSE};
enum LISTAS {BUILD01=0,ASPHALT,WALKWAY,POSTE,AP_BED,AP_BLUEBUTTON,AP_REDBUTTON,AP_LAMP,AP_COFFEE,AP_ELEVATOR,
                AP_KEYBOARD,AP_PILLOW,AP_SOFA,AP_PS4,AP_SERVERSIDE,AP_SERVERTOWER,AP_TAPETE,AP_WALL,AP_WIRE,AP_WOOD,AP_GLASS,AP_TOPHOUSE,
                MAIN_WINDOWS,MAIN_BODY,MAIN_LATERAL,MAIN_RING,MAIN_ELEVATOR,MAIN_GROUNDLIGHT,MAIN_LEAF,MAIN_WOOD,MAIN_VASE,MAIN_MESA,
                MAIN_TAPETE,MAIN_SOFA,MAIN_HALL_GENERIC,GROUND,AP_SERVERGLASS,SLAMP,CITY_LEAVES,CITY_TREES,CITY_GLASS};

using namespace std;

// ALthings
	enum AUDIO_BUFFER {AB_DOOR_OPEN=0, AB_ELEVATOR_RING, AB_M0};
	enum AUDIO_SOURCE {AS_DEFAULT=0,AS_HALLDOOR};

	// Buffers to hold sound data.
	ALuint al_buffer[100];

	// Sources are points of emitting sound.
	ALuint al_source[100];

	// Position of the source sound. -> arrays com 3 posições apenas	 
	// Velocity of the source sound.
	 
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
	GLuint inicio_lista; // Index do início da lista de visualização
	GLuint frame;

// GLMmodels
	ModelList modelList;

// Variavel "parametrica" correspondente ao tempo passado (utilizado pra fazer algumas coisas se moverem com o passar do tempo)
	double increment = 0;

// Posições de alguns objetos que se movem
	enum POSICOES{RHALLDOOR=0,LHALLDOOR,AIRPLANE,APELEVATOR};
	Ponto p[100];
	Ponto estrelas[NUM_ESTRELAS];

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
		if(loadALData(al_buffer[AB_M0],"sounds/Vance Joy - Lay It On Me (Said The Sky Remix).wav") == AL_FALSE)
		{
			printf("buffer_deuruim\n");
			exit(0);
		}
		// if(loadALData(al_buffer[AB_DOOR_OPEN],"sounds/Mike McDonough - Space Ship Door Sounds.wav") == AL_FALSE)
		// {
		// 	printf("buffer_deuruim\n");
		// 	exit(0);
		// }


	// Bind audio to a source
		//FONTE SONORA: PORTA/HALL
		// {
		// 	ALfloat pos[] = {0,0,450};
		// 	ALfloat vel[] = {0,0,0};
		// 	if(bindALData(al_buffer[AB_DOOR_OPEN],al_source[AS_HALLDOOR], pos, vel, AL_TRUE) == AL_FALSE)
		// 	{
		// 		printf("source_deuruim\n");
		// 		exit(0);
		// 	}
		// }
		// FONTE SONORA: SALA DE ESTAR {100,1354,830}
		{
			ALfloat pos[] = {100,100,100};
			ALfloat vel[] = {0,0,0};
			if(bindALData(al_buffer[AB_M0],al_source[AS_DEFAULT], pos, vel, AL_TRUE) == AL_FALSE)
			{
				printf("source_deuruim\n");
				exit(0);
			}
		}

	// Configure Listener initial values (estou configurando/ atualizando no update_callback)
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
	p[AIRPLANE].set(-1000,5000,15000,1);
	p[APELEVATOR].set(0,0,0,1);
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
		{ // apenas para criar/limitar escopo de a/b/c/d/e (SIM, È POSSÍVEL, TBM N TO ACREDITANDO Q CHUTEI E DEU CERTO)
			GLfloat a[] = {.25,.02,.2,1};
			glLightfv(GL_LIGHT0,GL_AMBIENT,a);

			GLfloat b[] = {.7,.6,.8,1};
			glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

			GLfloat c[] = {0,0,0,1};
			glLightfv(GL_LIGHT0,GL_SPECULAR,c);

			// GLfloat d[] = {0.5,1,0.866,0};
			GLfloat d[] = {0.5,1,0.866,0};
			glLightfv(GL_LIGHT0,GL_POSITION,d);

			GLfloat e[] = {0,0,0,1};
			glLightfv(GL_LIGHT0,GL_CONSTANT_ATTENUATION,e);
		} // Isso pq n encontrei uma forma bacana de reaproveitar o mesmo vetor atribuindo valores direto igual a {x1,x2,x3,x4}

		// glEnable(GL_LIGHT1);
		// { // apenas para criar/limitar escopo de a/b/c/d/e
		// 	GLfloat a[] = {.1,.1,.1,1};
		// 	glLightfv(GL_LIGHT1,GL_AMBIENT,a);

		// 	GLfloat b[] = {1,1,1,1};
		// 	glLightfv(GL_LIGHT1,GL_DIFFUSE,b);

		// 	GLfloat c[] = {.05,.1,.1,1};
		// 	glLightfv(GL_LIGHT1,GL_SPECULAR,c);

		// 	GLfloat d[] = {100,1352,800,1};
		// 	glLightfv(GL_LIGHT1,GL_POSITION,d);

		// 	GLfloat e[] = {.1,.1,.1,1};
		// 	glLightfv(GL_LIGHT1,GL_LINEAR_ATTENUATION,e);
		// }


	// Carregar obj
		modelList.build01 = glmReadOBJ("models/city/build01.obj");
		glmFacetNormals(modelList.build01);
		glmVertexNormals(modelList.build01, 90.0);
		glmScale(modelList.build01, 10);

		modelList.city_glass = glmReadOBJ("models/city/city_glass.obj");
		glmFacetNormals(modelList.city_glass);
		glmVertexNormals(modelList.city_glass, 90.0);
		glmScale(modelList.city_glass, 10);

		modelList.walkway = glmReadOBJ("models/city/walkway.obj");
		glmFacetNormals(modelList.walkway);
		glmVertexNormals(modelList.walkway, 90.0);
		glmScale(modelList.walkway, 10);

		modelList.asphalt = glmReadOBJ("models/city/asphalt.obj");
		glmFacetNormals(modelList.asphalt);
		glmVertexNormals(modelList.asphalt, 90.0);
		glmScale(modelList.asphalt, 10);

		modelList.city_trees = glmReadOBJ("models/city/wood.obj");
		glmFacetNormals(modelList.city_trees);
		glmVertexNormals(modelList.city_trees, 90.0);
		glmScale(modelList.city_trees, 10);

		modelList.city_leaves = glmReadOBJ("models/city/leaves.obj");
		glmFacetNormals(modelList.city_leaves);
		glmVertexNormals(modelList.city_leaves, 90.0);
		glmScale(modelList.city_leaves, 10);

		modelList.torre = glmReadOBJ("models/torre/torre.obj");
		glmFacetNormals(modelList.torre);
		glmVertexNormals(modelList.torre, 90.0);
		glmScale(modelList.torre, 20);

		modelList.aura = glmReadOBJ("models/torre/3daura.obj");
		glmFacetNormals(modelList.aura);
		glmVertexNormals(modelList.aura, 90.0);
		glmScale(modelList.aura, 15);

		modelList.main_body = glmReadOBJ("models/predio/main_body.obj");
		glmFacetNormals(modelList.main_body);
		glmVertexNormals(modelList.main_body, 90.0);
		glmScale(modelList.main_body, 10);

		modelList.main_window = glmReadOBJ("models/predio/main_window.obj");
		glmFacetNormals(modelList.main_window);
		glmVertexNormals(modelList.main_window, 90.0);
		glmScale(modelList.main_window, 10);

		modelList.main_insidewindow = glmReadOBJ("models/predio/main_insidewindow.obj");
		glmFacetNormals(modelList.main_insidewindow);
		glmVertexNormals(modelList.main_insidewindow, 90.0);
		glmScale(modelList.main_insidewindow, 10);

		modelList.main_ring = glmReadOBJ("models/predio/main_ring.obj");
		glmFacetNormals(modelList.main_ring);
		glmVertexNormals(modelList.main_ring, 90.0);
		glmScale(modelList.main_ring, 10);

		modelList.main_elevator = glmReadOBJ("models/predio/main_elevator.obj");
		glmFacetNormals(modelList.main_elevator);
		glmVertexNormals(modelList.main_elevator, 90.0);
		glmScale(modelList.main_elevator, 10);

		modelList.main_lateral = glmReadOBJ("models/predio/main_lateral.obj");
		glmFacetNormals(modelList.main_lateral);
		glmVertexNormals(modelList.main_lateral, 90.0);
		glmScale(modelList.main_lateral, 10);

		modelList.main_hall_generic = glmReadOBJ("models/predio/main_hall_generic.obj");
		glmFacetNormals(modelList.main_hall_generic);
		glmVertexNormals(modelList.main_hall_generic, 90.0);
		glmScale(modelList.main_hall_generic, 10);

		modelList.main_bot = glmReadOBJ("models/predio/main_bot.obj");
		glmFacetNormals(modelList.main_bot);
		glmVertexNormals(modelList.main_bot, 90.0);
		glmScale(modelList.main_bot, 10);

		modelList.main_groundlight = glmReadOBJ("models/predio/main_groundlight.obj");
		glmFacetNormals(modelList.main_groundlight);
		glmVertexNormals(modelList.main_groundlight, 90.0);
		glmScale(modelList.main_groundlight, 10);

		modelList.main_leaf = glmReadOBJ("models/predio/main_leaf.obj");
		glmFacetNormals(modelList.main_leaf);
		glmVertexNormals(modelList.main_leaf, 90.0);
		glmScale(modelList.main_leaf, 10);

		modelList.main_wood = glmReadOBJ("models/predio/main_wood.obj");
		glmFacetNormals(modelList.main_wood);
		glmVertexNormals(modelList.main_wood, 90.0);
		glmScale(modelList.main_wood, 10);

		modelList.main_vase = glmReadOBJ("models/predio/main_vase.obj");
		glmFacetNormals(modelList.main_vase);
		glmVertexNormals(modelList.main_vase, 90.0);
		glmScale(modelList.main_vase, 10);

		modelList.main_mesa = glmReadOBJ("models/predio/main_mesa.obj");
		glmFacetNormals(modelList.main_mesa);
		glmVertexNormals(modelList.main_mesa, 90.0);
		glmScale(modelList.main_mesa, 10);

		modelList.main_tapete = glmReadOBJ("models/predio/main_tapete.obj");
		glmFacetNormals(modelList.main_tapete);
		glmVertexNormals(modelList.main_tapete, 90.0);
		glmScale(modelList.main_tapete, 10);

		modelList.main_sofa = glmReadOBJ("models/predio/main_sofa.obj");
		glmFacetNormals(modelList.main_sofa);
		glmVertexNormals(modelList.main_sofa, 90.0);
		glmScale(modelList.main_sofa, 10);

		modelList.main_hdoor = glmReadOBJ("models/predio/main_rhdoor.obj");
		glmFacetNormals(modelList.main_hdoor);
		glmVertexNormals(modelList.main_hdoor, 90.0);
		glmScale(modelList.main_hdoor, 10);

		modelList.ap_bed = glmReadOBJ("models/predio/ap_bed.obj");
		glmFacetNormals(modelList.ap_bed);
		glmVertexNormals(modelList.ap_bed, 90.0);
		glmScale(modelList.ap_bed, 10);

		modelList.ap_bluebutton = glmReadOBJ("models/predio/ap_bluebutton.obj");
		glmFacetNormals(modelList.ap_bluebutton);
		glmVertexNormals(modelList.ap_bluebutton, 90.0);
		glmScale(modelList.ap_bluebutton, 10);

		modelList.ap_coffee = glmReadOBJ("models/predio/ap_coffee.obj");
		glmFacetNormals(modelList.ap_coffee);
		glmVertexNormals(modelList.ap_coffee, 90.0);
		glmScale(modelList.ap_coffee, 10);

		modelList.ap_elevator = glmReadOBJ("models/predio/ap_elevator.obj");
		glmFacetNormals(modelList.ap_elevator);
		glmVertexNormals(modelList.ap_elevator, 90.0);
		glmScale(modelList.ap_elevator, 10);

		modelList.ap_elevatorglass = glmReadOBJ("models/predio/ap_elevatorglass.obj");
		glmFacetNormals(modelList.ap_elevatorglass);
		glmVertexNormals(modelList.ap_elevatorglass, 90.0);
		glmScale(modelList.ap_elevatorglass, 10);

		modelList.ap_glass = glmReadOBJ("models/predio/ap_glass.obj");
		glmFacetNormals(modelList.ap_glass);
		glmVertexNormals(modelList.ap_glass, 90.0);
		glmScale(modelList.ap_glass, 10);

		modelList.ap_homeroom_monitor = glmReadOBJ("models/predio/ap_homeroom_monitor.obj");
		glmFacetNormals(modelList.ap_homeroom_monitor);
		glmVertexNormals(modelList.ap_homeroom_monitor, 90.0);
		glmScale(modelList.ap_homeroom_monitor, 10);

		modelList.ap_keyboard = glmReadOBJ("models/predio/ap_keyboard.obj");
		glmFacetNormals(modelList.ap_keyboard);
		glmVertexNormals(modelList.ap_keyboard, 90.0);
		glmScale(modelList.ap_keyboard, 10);

		modelList.ap_lamp = glmReadOBJ("models/predio/ap_lamp.obj");
		glmFacetNormals(modelList.ap_lamp);
		glmVertexNormals(modelList.ap_lamp, 90.0);
		glmScale(modelList.ap_lamp, 10);

		modelList.ap_pillow = glmReadOBJ("models/predio/ap_pillow.obj");
		glmFacetNormals(modelList.ap_pillow);
		glmVertexNormals(modelList.ap_pillow, 90.0);
		glmScale(modelList.ap_pillow, 10);

		modelList.ap_sofa = glmReadOBJ("models/predio/ap_sofa.obj");
		glmFacetNormals(modelList.ap_sofa);
		glmVertexNormals(modelList.ap_sofa, 90.0);
		glmScale(modelList.ap_sofa, 10);

		modelList.ap_ps4 = glmReadOBJ("models/predio/ap_ps4.obj");
		glmFacetNormals(modelList.ap_ps4);
		glmVertexNormals(modelList.ap_ps4, 90.0);
		glmScale(modelList.ap_ps4, 10);

		modelList.ap_redbutton = glmReadOBJ("models/predio/ap_redbutton.obj");
		glmFacetNormals(modelList.ap_redbutton);
		glmVertexNormals(modelList.ap_redbutton, 90.0);
		glmScale(modelList.ap_redbutton, 10);

		modelList.ap_serverglass = glmReadOBJ("models/predio/ap_serverglass.obj");
		glmFacetNormals(modelList.ap_serverglass);
		glmVertexNormals(modelList.ap_serverglass, 90.0);
		glmScale(modelList.ap_serverglass, 10);

		modelList.ap_serverside = glmReadOBJ("models/predio/ap_serverside.obj");
		glmFacetNormals(modelList.ap_serverside);
		glmVertexNormals(modelList.ap_serverside, 90.0);
		glmScale(modelList.ap_serverside, 10);

		modelList.ap_servertower = glmReadOBJ("models/predio/ap_servertower.obj");
		glmFacetNormals(modelList.ap_servertower);
		glmVertexNormals(modelList.ap_servertower, 90.0);
		glmScale(modelList.ap_servertower, 10);

		modelList.ap_superpc = glmReadOBJ("models/predio/ap_superpc.obj");
		glmFacetNormals(modelList.ap_superpc);
		glmVertexNormals(modelList.ap_superpc, 90.0);
		glmScale(modelList.ap_superpc, 10);

		modelList.ap_tapete = glmReadOBJ("models/predio/ap_tapete.obj");
		glmFacetNormals(modelList.ap_tapete);
		glmVertexNormals(modelList.ap_tapete, 90.0);
		glmScale(modelList.ap_tapete, 10);

		modelList.ap_tophouse = glmReadOBJ("models/predio/ap_tophouse.obj");
		glmFacetNormals(modelList.ap_tophouse);
		glmVertexNormals(modelList.ap_tophouse, 90.0);
		glmScale(modelList.ap_tophouse, 10);

		modelList.ap_wall = glmReadOBJ("models/predio/ap_wall.obj");
		glmFacetNormals(modelList.ap_wall);
		glmVertexNormals(modelList.ap_wall, 90.0);
		glmScale(modelList.ap_wall, 10);

		modelList.ap_white = glmReadOBJ("models/predio/ap_white.obj");
		glmFacetNormals(modelList.ap_white);
		glmVertexNormals(modelList.ap_white, 90.0);
		glmScale(modelList.ap_white, 10);

		modelList.ap_wire = glmReadOBJ("models/predio/ap_wire.obj");
		glmFacetNormals(modelList.ap_wire);
		glmVertexNormals(modelList.ap_wire, 90.0);
		glmScale(modelList.ap_wire, 10);

		modelList.ap_wood = glmReadOBJ("models/predio/ap_wood.obj");
		glmFacetNormals(modelList.ap_wood);
		glmVertexNormals(modelList.ap_wood, 90.0);
		glmScale(modelList.ap_wood, 10);

		modelList.ground = glmReadOBJ("models/predio/ground.obj");
		glmFacetNormals(modelList.ground);
		glmVertexNormals(modelList.ground, 90.0);
		glmScale(modelList.ground, 10);

		modelList.cloud = glmReadOBJ("models/city/cloud.obj");
		glmFacetNormals(modelList.cloud);
		glmVertexNormals(modelList.cloud, 90.0);
		glmScale(modelList.cloud, 10);

		modelList.poste = glmReadOBJ("models/city/poste.obj");
		glmFacetNormals(modelList.poste);
		glmVertexNormals(modelList.poste, 90.0);
		glmScale(modelList.poste, 10);

		modelList.sLamp = glmReadOBJ("models/city/streetLamp.obj");
		glmFacetNormals(modelList.sLamp);
		glmVertexNormals(modelList.sLamp, 90.0);
		glmScale(modelList.sLamp, 10);

		modelList.airplane = glmReadOBJ("models/city/plane.obj");
		glmFacetNormals(modelList.airplane);
		glmVertexNormals(modelList.airplane, 90.0);
		glmScale(modelList.airplane, 40);

		initPos();

	// Preencher vetor pos de estrelas
		for(int x=0, area=128000; x<NUM_ESTRELAS ;x++)
		{
			int vx = rand()%area-area/2; // vy = vx (valor de y = valor de x)(expressão apenas)
			int vz = rand()%area-area/2;
			int vy = rand()%8000+40000-sqrt(vx*vx + vz*vz)/1.5; // quanto mais longe do centro, mais baixo (pra dar a impressão de globo)
			estrelas[x].set(vx,vy,vz,1);
		}

	// Carregar listas de visualização
		inicio_lista = generateDisplayLists(modelList);

	// Gerar lista do frame (para poder ser reutilizado na draw_callback a fim de evitar "flickering")
		frame = glGenLists(1);
}

void drawText(void* font, string str, double x, double y)
{
	// glPushMatrix();

		// glTranslatef(0,0,10);
		// glScalef(100,100,100);
		glRasterPos2d(x,y);

		for(int i=0;i<str.size();i++)
		glutBitmapCharacter(font,str[i]);

	// glPopMatrix();
}

double from0toX(double x,double defasamento,double spd)
{
	return ((sin((increment + defasamento)*spd*M_PI/180)+1)/2.0)/(1.0/x);

	// ((sin(increment)+1)/20.0) retorna um valor entre 0 e 1
	//	^^^^^^^^^^^^^^^^^^^^^^^ /(1.0/x) retorna um valor de 0 até X
}

void draw_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// if(cam.display_text!="")
	// 	glutWireCube(10);

	//	Criar lista para guardar desenho todo 
	//	Resolve problema de objetos piscando na tela (pode ser estranho a solução, mas resolveu)(parte...)
	glNewList(frame, GL_COMPILE);
	
	glPushMatrix();
		gluLookAt(cam.eye.x+(cos((cam.bob/2)*M_PI/180)/50),cam.ground+cam.height+cam.eye.y+(sin(cam.bob*M_PI/180)/80),cam.eye.z,
					cam.eye.x+sin(cam.degree*M_PI/180),cam.ground+cam.height+cam.eye.y+sin(cam.vdegree*M_PI/180),cam.eye.z+cos(cam.degree*M_PI/180),
					0,1,0);

		// Sun
			drawSun(.01*(increment-7200));

			drawMoon(.01*(increment+7200));

		// Clouds
			glPushMatrix();
				emissive(.6);
					glRotatef(increment/60,0,1,0);
					glTranslatef(0,50000,0);
					glColor4f(1,1,1,.7);
					glScalef(1000,1000,1000);
					glmDraw(modelList.cloud,GLM_SMOOTH);
				emissive(0);
			glPopMatrix();

		// Estrelas
			emissive(1);
				for(int x=0; x<NUM_ESTRELAS; x++)
				{
					glColor4f(1,1,1,from0toX(1,x,1));	
					drawSolidCube(estrelas[x].x,estrelas[x].y,estrelas[x].z,rand()%361,rand()%361,from0toX(100,x,1)+100);	
				}
			emissive(0);

		// Cidade
			glCallList(inicio_lista+CITY_GLASS);
			glCallList(inicio_lista+CITY_TREES);
			glCallList(inicio_lista+CITY_LEAVES);
			glCallList(inicio_lista+BUILD01);
			glCallList(inicio_lista+ASPHALT);
			glCallList(inicio_lista+WALKWAY);
			glCallList(inicio_lista+POSTE);

			glColor4f(1,1,1,1);
			drawModel(0+p[AIRPLANE].x,-10+p[AIRPLANE].y,500+p[AIRPLANE].z,180,0,modelList.airplane,GLM_FLAT | GLM_MATERIAL);

		// Predio
				glCallList(inicio_lista+MAIN_WINDOWS);

		// Apartamento
			glCallList(inicio_lista+AP_BED);
			emissive(from0toX(.5,0,1));
				glCallList(inicio_lista+AP_BLUEBUTTON);
				glCallList(inicio_lista+AP_REDBUTTON);
				glCallList(inicio_lista+AP_LAMP);
			emissive(0);
			glCallList(inicio_lista+AP_COFFEE);
			glCallList(inicio_lista+AP_ELEVATOR);
			glCallList(inicio_lista+AP_KEYBOARD);
			glCallList(inicio_lista+AP_PILLOW);
			glCallList(inicio_lista+AP_SOFA);
			glCallList(inicio_lista+AP_PS4);
			glCallList(inicio_lista+AP_SERVERSIDE);
			glCallList(inicio_lista+AP_SERVERTOWER);
			glCallList(inicio_lista+AP_TAPETE);
			glCallList(inicio_lista+AP_WALL);
			glCallList(inicio_lista+AP_WIRE);
			glCallList(inicio_lista+AP_WOOD);
			glCallList(inicio_lista+AP_GLASS);
			glCallList(inicio_lista+AP_TOPHOUSE);
			emissive(from0toX(.4,60,1));	
				glColor4f(from0toX(.6,0,4),from0toX(1,30,4),from0toX(1,60,4),.9);
				drawModel(0,-10,500,180,0,modelList.ap_superpc,GLM_FLAT | GLM_MATERIAL);
				glColor4f(from0toX(.6,30,4),from0toX(1,60,4),from0toX(1,120,4),.9);
				drawModel(0,-10,500,180,0,modelList.ap_homeroom_monitor,GLM_FLAT | GLM_MATERIAL);
			emissive(0);

		// Prédio
			glCallList(inicio_lista+MAIN_BODY);
			glCallList(inicio_lista+MAIN_LATERAL);
			glCallList(inicio_lista+MAIN_RING);
			glCallList(inicio_lista+MAIN_ELEVATOR);
			glColor4f(.2,.7,.45,1);
			drawModel(0,-10+sin(increment*M_PI/180),500,180,0,modelList.main_bot,GLM_FLAT | GLM_MATERIAL);
			glCallList(inicio_lista+MAIN_GROUNDLIGHT);
			glCallList(inicio_lista+MAIN_LEAF);
			glCallList(inicio_lista+MAIN_WOOD);
			glCallList(inicio_lista+MAIN_VASE);
			glCallList(inicio_lista+MAIN_MESA);
			glCallList(inicio_lista+MAIN_TAPETE);
			glCallList(inicio_lista+MAIN_SOFA);
			glCallList(inicio_lista+MAIN_HALL_GENERIC);
			emissive(.2);
				glColor4f(.4,1,1,.5);
				drawModel(0+(p[LHALLDOOR]).x,-10+(p[LHALLDOOR]).y,500+(p[LHALLDOOR]).z,180,0,modelList.main_hdoor,GLM_FLAT | GLM_MATERIAL);
				drawModel(0+(p[RHALLDOOR]).x,-10+(p[RHALLDOOR]).y,500+(p[RHALLDOOR]).z,180,0,modelList.main_hdoor,GLM_FLAT | GLM_MATERIAL);
			emissive(0);

		// Montanhas
			glCallList(inicio_lista+GROUND);

		// Apartamento (ainda)
			glCallList(inicio_lista+AP_SERVERGLASS);
			glColor4f(.1,.5,.5,.3);
			drawModel(0,-10+p[APELEVATOR].y,500,180,0,modelList.ap_elevatorglass,GLM_FLAT | GLM_MATERIAL);


		// OBS: o que precisa ser desenhado com transparencia precisa ser desenhado por último
			glCallList(inicio_lista+SLAMP);

	glPopMatrix();

	glPushMatrix();
	    glTranslatef(0,0,-10);
	    glColor4f(1,1,1,1);
		glDisable(GL_DEPTH_TEST);	// Evita que, eventualmente, algo venha a ficar entre a camera e o texto (não o mostrando)
	    // drawText(GLUT_BITMAP_HELVETICA_18,cam.display_text.c_str(),0,0);		// Muito lag ainda, não sei pq
	    glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glEndList();	// Fecha lista de desenho
	glCallList(frame);	// Envia a lista pronta para ser desenhada
	glDeleteLists(frame, 1);	// Deleta a lista usada
	
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
	if(keyState['I'])
		increment+=200;

	glutTimerFunc(((double)1000)/FPS,update_callback,0); 
	// glutPostRedisplay();
}

void idle_callback()	// MAX FPS BRO!! (NO MORE ;_; Idle n surte mais esse efeito - cena mt pesada)
{										//(É necessario forçar a atualização no FPS)
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
	// Cam Warp / mudar de andar
	if(keyState['r'] && cam.canWarp == 1)
	{
		cam.ground=1352;
		cam.eye.y=0;
		cam.eye.x=0;
		cam.eye.z=1133.5;
		cam.degree=180;
		cam.apLimit();
	}
	else if(keyState['r'] && cam.canWarp == 2)
	{
		if(keyState['r'])
		{
			cam.ground=0;
			cam.eye.y=0;
			cam.eye.x=-110;
			cam.eye.z=780;
			cam.degree=180;
			cam.groundLimit();
		}
	}


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
			cam.degree-=cam.mousesense;
		else if(x<cam.mlast.x)
			cam.degree+=cam.mousesense;

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
	glutFullScreen();

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
