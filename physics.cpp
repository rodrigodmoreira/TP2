#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "player.h"

using namespace std;

void calculatePhysics(int* keyState,Camera &cam)
{
	// Setar velocidade -> correr/andar
	if(keyState[' '])
		cam.spd=2;
	else
		cam.spd=1;
	
	// Movimentação
	if(keyState['w'])
	{
		cam.eye.x+=cam.spd*sin(cam.degree*M_PI/180);
		cam.eye.z+=cam.spd*cos(cam.degree*M_PI/180);
	}
	if(keyState['s'])
	{
		cam.eye.x-=cam.spd*sin(cam.degree*M_PI/180);
		cam.eye.z-=cam.spd*cos(cam.degree*M_PI/180);
	}
	if(keyState['a'])
	{
		cam.degree+=2;
	}
	if(keyState['d'])
	{
		cam.degree-=2;
	}
	if(keyState['q'])
	{
		cam.eye.x+=cam.spd*sin((cam.degree+90)*M_PI/180);
		cam.eye.z+=cam.spd*cos((cam.degree+90)*M_PI/180);
	}
	if(keyState['e'])
	{
		cam.eye.x-=cam.spd*sin((cam.degree+90)*M_PI/180);
		cam.eye.z-=cam.spd*cos((cam.degree+90)*M_PI/180);
	}

	// Realiza movimentação da cabeça
	if(!(keyState['w']||keyState['s']||keyState['a']||keyState['d']||keyState['q']||keyState['e']))
		cam.bob+=2;
	else
		cam.bob+=10;
}