#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

void drawWireCube(double x,double y,double z,double size)
{
	size/=2;
	glPushMatrix();
	
	    glTranslatef (x, y+size, z);
        //glutWireCube (size);
	    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        glBegin(GL_TRIANGLE_STRIP);
        	glVertex3d(-size,0,size);
        	glVertex3d(size,0,size);
        	glVertex3d(size,0,-size);
        	glVertex3d(-size,0,-size);
        	glVertex3d(-size,size*2,-size);
        	glVertex3d(size,size*2,-size);
        	glVertex3d(size,size*2,size);
        	glVertex3d(-size,size*2,size);
        glEnd();

	    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glPopMatrix();
}

void drawPlane(double x,double y, double z, double size)
{
	size/=2;
	glPushMatrix();
	
	    glTranslatef (x, y, z);
        
        glBegin(GL_TRIANGLE_FAN);
        	glVertex3d(-size,0,-size);
        	glVertex3d(size,0,-size);
        	glVertex3d(size,0,size);
        	glVertex3d(-size,0,size);
        glEnd();
	
	glPopMatrix();
}