#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib> 

#include "player.h"

enum CAM_MODE { C_KB=0,C_MOUSE};
enum POSICOES{RHALLDOOR=0,LHALLDOOR,AIRPLANE,APELEVATOR};

using namespace std;

double from0toX(double x,double defasamento,double spd,double increment)
{
	return ((sin((increment + defasamento)*spd*M_PI/180)+1)/2.0)/(1.0/x);

	// ((sin(increment)+1)/20.0) retorna um valor entre 0 e 1
	//	^^^^^^^^^^^^^^^^^^^^^^^ /(1.0/x) retorna um valor de 0 até X
}

void calculatePhysics(int* keyState,Camera &cam,Ponto *p,double increment)
{
	// Checar se está perto da porta de entrada
		if(cam.eye.x >= -25 && cam.eye.x <= 25 && cam.eye.z <= 505 && cam.eye.z >= 405)
		{
			if(p[RHALLDOOR].x<50)	// Enquanto não chegar ao limite, continua abrindo
				p[RHALLDOOR].x++;

			if(p[LHALLDOOR].x>-25)
				p[LHALLDOOR].x--;
		}
		else
		{
			if(p[RHALLDOOR].x>25)	// Enquanto não chegar ao limite, continua fechando
				p[RHALLDOOR].x--;

			if(p[LHALLDOOR].x<0)
				p[LHALLDOOR].x++;
		}

	// Checar se está perto da porta do elevador
		if(cam.eye.x >= -25 && cam.eye.x <= 25 && cam.eye.z <= 1145 && cam.eye.z >= 1025)
		{
			if(p[APELEVATOR].y>-150) // Mesmo o elevador estando lá em cima, dentro do obj, seu centro está no (0,0)
				p[APELEVATOR].y-=2;
		}
		else
		{
			if(p[APELEVATOR].y<0)
				p[APELEVATOR].y+=2;	
		}

	// Checar se está perto do elevador
		if(cam.ground >=-5 && cam.ground <=5) // Se está no terra
		{
			if((cam.eye.x >= -120 && cam.eye.x <= -100 && cam.eye.z <= 795 && cam.eye.z >= 765) ||
				(cam.eye.x <= 120 && cam.eye.x >= 100 && cam.eye.z <= 795 && cam.eye.z >= 765) )
			{
				cam.display_text=1;
			}
			else
			{
				cam.display_text=0;
			}
		}
		else if(cam.ground >= 1345 && cam.ground <= 1360) // Se está no apartamento
		{
			if(cam.eye.x >= -25 && cam.eye.x <= 25 && cam.eye.z <= 1145 && cam.eye.z >= 1125 && cam.ground >=-5)
			{
				cam.display_text=2;
			}
			else
			{
				cam.display_text=0;
			}
		}

	// Gravidade
		cam.eye.y+=cam.vspd;
		
		if(cam.eye.y+cam.vspd>cam.ground)
		{
			cam.vspd-=.2;
		}
		else
		{
			cam.vspd=0;
			cam.eye.y=cam.ground;
		}

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
			if(!(keyState['w']||keyState['s']||keyState['a']||keyState['d']||keyState['q']||keyState['e'])) // Caso esteja parado
			{
				// Fov
					if(cam.fov>65)
						cam.fov-=1;
					else
						cam.fov=65;
			}
			else
			{
				// fov
				if(cam.fov<80)
					cam.fov+=.4;
			}

			cam.spd=2;
			cam.bob+=5;
		}
		else
		{

			if(!(keyState['w']||keyState['s']||keyState['a']||keyState['d']||keyState['q']||keyState['e'])) // Caso esteja parado
			{
				// Fov
					if(cam.fov>65)
						cam.fov-=1;
					else
						cam.fov=65;
			}
			else
			{
				// fov
				if(cam.fov<70)
					cam.fov+=.1;
			}

			cam.spd=1;
		}
	
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
			GLfloat a[] = {from0toX(.1,0,.01,increment),from0toX(.1,0,.01,increment),from0toX(.1,0,.01,increment),1};
			glLightfv(GL_LIGHT0,GL_AMBIENT,a);

			GLfloat b[] = {.1+from0toX(.1,0,.01,increment),.1+from0toX(.1,0,.01,increment),.1+from0toX(.1,0,.01,increment),1};
			glLightfv(GL_LIGHT0,GL_DIFFUSE,b);

		// Fazer a cor do ceu diminuir com o passar do tempo e, quando atingir um nivel mínimo, ao invés de ficar preto, fica azul escuro
			// 0.4, 0.8, 1.0, 1.0 //0.2 0.8 1
			double colorR = from0toX(.2,0,.01,increment);
			double colorG = from0toX(.8,0,.01,increment);
			double colorB = from0toX(1,0,.01,increment);
			if(colorB <= .1)
			{
				colorR=0;
				colorG=.05;
				colorB=.1;
			}
			glClearColor(colorR, colorG, colorB, 1.0);
	}

	// Movimento avião
		p[AIRPLANE].z-=50;
		p[AIRPLANE].y+=2*sin(10*increment*M_PI/180);
		p[AIRPLANE].x+=2*cos(10*increment*M_PI/180);
		if(p[AIRPLANE].z<=-20000)
		{
			p[AIRPLANE].z=15000;
			p[AIRPLANE].x=-2000+rand()%4001;
		}
}