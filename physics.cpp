#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "player.h"

enum CAM_MODE { C_KB=0,C_MOUSE};

using namespace std;

void calculatePhysics(int* keyState,Camera &cam)
{
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
	if(!(keyState['w']||keyState['s']||keyState['a']||keyState['d']||keyState['q']||keyState['e']))
		cam.bob+=2;
	else
		cam.bob+=10;
}