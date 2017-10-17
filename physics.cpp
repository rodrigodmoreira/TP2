#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <string>

#include "player.h"

enum CAM_MODE { C_KB=0,C_MOUSE};

using namespace std;

void calculatePhysics(int* keyState,Camera &cam)
{
	// Checar se está perto do elevador
	if(cam.eye.x >= -120 && cam.eye.x <= -100 && cam.eye.z <= 795 && cam.eye.z >= 775)
	{
		cam.display_text = "Pressione E para subir o elevador";
		cout << cam.display_text << endl;
	}
	else
		cam.display_text = "";

	// Gravidade
	if(cam.eye.y+cam.vspd>0)
	{
		cam.vspd-=.2;
	}
	else
	{
		cam.vspd=0;
		cam.eye.y=0;
	}
	cam.eye.y+=cam.vspd;

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
		cam.spd=2;
		cam.bob+=5;
	}
	else
		cam.spd=1;
	
	// Movimentação
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
}