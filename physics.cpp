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
		cam.dir={0,0,-1,0};
		cam.spd=abs(cam.spd); // anda pra frente
		cout << "cam.spd" << cam.spd << endl;
		/*gluLookAt(cam.spd*cam.dir.x, cam.spd*cam.dir.y, cam.spd*cam.dir.z,
		    0, 0, -2,
		    0, 1, 0);*/

		gluLookAt(cam.spd*cam.dir.x,cam.spd*cam.dir.y,cam.spd*cam.dir.z,
		        cam.dir.x,cam.dir.y,cam.dir.z,
		        0,1,0);
	}
	else if(keyState['s'])
	{
		cam.dir={0,0,-1,0};
		cam.spd=-abs(cam.spd); // anda pra trás
		/*gluLookAt(0, 0, 1,
		    0, 0, -2,
		    0, 1, 0);*/
		cout << "cam.spd" << cam.spd << endl;

		gluLookAt(cam.spd*cam.dir.x,cam.spd*cam.dir.y,cam.spd*cam.dir.z,
		        cam.dir.x,cam.dir.y,cam.dir.z,
		        0,1,0);
	}
	else
	{
		if(keyState['a'])
		{
		  cam.dir={-1*sin(2*M_PI/180),0,-1*cos(2*M_PI/180),0};
		  /*gluLookAt(0, 0, 0,
		      -2, 0, 0,
		      0, 1, 0);*/

		  gluLookAt(0,0,0,
		        cam.dir.x,cam.dir.y,cam.dir.z,
		        0,1,0);
		}
		if(keyState['d'])
		{
		  cam.dir={1*sin(2*M_PI/180),0,-1*cos(2*M_PI/180),0};
		  /*gluLookAt(0, 0, 0,
		      2, 0, 0,
		      0, 1, 0);*/

		  gluLookAt(0,0,0,
		        cam.dir.x,cam.dir.y,cam.dir.z,
		        0,1,0);
		}
	}


	if(keyState['r'])
	{
	glLoadIdentity();
	}  
}