#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <string>
#include <random>

#include "player.h"

enum CAM_MODE { C_KB=0,C_MOUSE};
enum POSICOES{RHALLDOOR=0,LHALLDOOR,PLANE};

using namespace std;

void calculatePhysics(int* keyState,Camera &cam,Ponto *p,double increment)
{
	// Checar se está perto da porta de entrada
		if(cam.eye.x >= -25 && cam.eye.x <= 25 && cam.eye.z <= 505 && cam.eye.z >= 405 || keyState['c'])
		{
			if(p[RHALLDOOR].x<50)
				p[RHALLDOOR].x++;

			if(p[LHALLDOOR].x>-25)
				p[LHALLDOOR].x--;
		}
		else
		{
			if(p[RHALLDOOR].x>25)
				p[RHALLDOOR].x--;

			if(p[LHALLDOOR].x<0)
				p[LHALLDOOR].x++;
		}

	// Checar se está perto do elevador
		if(cam.eye.x >= -120 && cam.eye.x <= -100 && cam.eye.z <= 795 && cam.eye.z >= 775 && cam.ground >=-5 && cam.ground <=5)
		{
			cam.display_text = "Pressione R para subir o elevador";
			if(keyState['r'])
			{
				cam.ground=1350;
				cam.apLimit();
			}
			cout << cam.display_text << endl;
		}
		else
			cam.display_text = "";

	// Gravidade
		if(cam.eye.y+cam.vspd>cam.ground)
		{
			cam.vspd-=.2;
		}
		else
		{
			cam.vspd=0;
			cam.eye.y=cam.ground;
		}
		cam.eye.y+=cam.vspd;

	// Subir e descer a camera
		if(keyState['+'])
		{
			cam.vspd=0;
			cam.eye.y+=10;
		}
		if(keyState['-'])
		{
			cam.vspd=0;
			cam.eye.y-=10;
		}

	// Setar velocidade -> correr/andar
		if(keyState[' '])
		{
			cam.spd=20;
			cam.bob+=5;
		}
		else
			cam.spd=1;
	
	// Movimentação
		// Checar se não atingiu os limites delimitados pela área em que estou (chão ou apartamento)
		if(keyState['w'])
			cam.walkFoward();
		if(keyState['s'])
			cam.walkBackward();

		if(cam.mode == C_KB)
		{
			if(keyState['a'])
				cam.degree+=2;
			if(keyState['d'])
				cam.degree-=2;
			if(keyState['q'])
				cam.walkSideL();
			if(keyState['e'])
				cam.walkSideR();
		}
		else if(cam.mode == C_MOUSE)
		{
			if(keyState['a'])
				cam.walkSideL();
			if(keyState['d'])
				cam.walkSideR();
		}

	// Realiza movimentação da cabeça
		if(!(keyState['w']||keyState['s']||keyState['a']||keyState['d']||keyState['q']||keyState['e'])) // Caso esteja parado
		{
			cam.bob+=2;	// Sacudir levemente a camera

			cam.hspd=0;
			/*if(cam.hspd>0)
				cam.hspd-=.01;
			else
				cam.hspd=0;*/ //Para fricção, será necessário manter atualizando sempre o "walkFoward", algo que não acontece na lógica atual
		}
		else	// Caso esteja andando
		{
			cam.bob+=10;	// Sacudir a camera fortemente

			if(cam.hspd<1)
				cam.hspd+=.05;
			else
				cam.hspd=1;
		}

	// Ciclo dia e noite
	{
		// Configura a luminosidade da fonte de luz
			GLfloat a[] = {cos(.011*increment*M_PI/180)/10,cos(.011*increment*M_PI/180)/10,cos(.011*increment*M_PI/180)/10,1};
			glLightfv(GL_LIGHT0,GL_AMBIENT,a);

			GLfloat b[] = {.1+cos(.011*increment*M_PI/180)/5,.1+cos(.011*increment*M_PI/180)/5,.1+cos(.011*increment*M_PI/180)/5,1};
			glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

		// Fazer a cor do ceu diminuir com o passar do tempo e, quando atingir um nivel mínimo, ao invés de ficar preto, fica azul escuro
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

	// Movimento avião
	p[PLANE].z-=20;
	if(p[PLANE].z<=-20000)
	{
		minstd_rand0 generator;
		p[PLANE].z=15000;
		p[PLANE].x=-500+generator()%1001;
	}
}