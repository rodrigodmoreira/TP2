#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "player.h"

using namespace std;

void calculatePhysics(int* keyState,Camera &cam)
{	
	if(keyState['w'])
	{
		cam.eye.x+=1*sin(cam.degree*M_PI/180);
		cam.eye.z+=1*cos(cam.degree*M_PI/180);
	}
	if(keyState['s'])
	{
		cam.eye.x-=1*sin(cam.degree*M_PI/180);
		cam.eye.z-=1*cos(cam.degree*M_PI/180);
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
		cam.eye.x+=1*sin((cam.degree+90)*M_PI/180);
		cam.eye.z+=1*cos((cam.degree+90)*M_PI/180);
	}
	if(keyState['e'])
	{
		cam.eye.x-=1*sin((cam.degree+90)*M_PI/180);
		cam.eye.z-=1*cos((cam.degree+90)*M_PI/180);
	}

	if(!(keyState['w']||keyState['s']||keyState['a']||keyState['d']||keyState['q']||keyState['e']))
		cam.bob=0;
	else
		cam.bob+=10;


	if(keyState['r'])
	{
		glLoadIdentity();
	}  
}