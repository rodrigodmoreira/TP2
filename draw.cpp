#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "objloader.h"

using namespace std;

void drawModel(double x,double y, double z, GLMmodel* model, GLuint shading)
{
        glPushMatrix();
                glTranslatef(x,y,z);
                glmDraw(model,shading);
        glPopMatrix();
}

void drawWireCube(double x,double y,double z,double size)
{
	size/=2;
	glPushMatrix();
	
	    glTranslatef (x, y+size, z);
        //glutWireCube (size);
	    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        glBegin(GL_TRIANGLE_FAN);

                glColor3f(  0,  0, 1.0 );
                glVertex3d(-size/2,-size/2,-size/2);
                glVertex3d(-size/2,size/2,-size/2);
                glVertex3d(size/2,size/2,-size/2);
                glVertex3d(size/2,-size/2,-size/2);
                //glVertex3d(-size/2,-size/2,-size/2);

                glColor3f(   0,  0, 1.0 );
                glVertex3d(-size/2,-size/2,size/2);
                glVertex3d(-size/2,size/2,size/2);
                glVertex3d(size/2,size/2,size/2);
                glVertex3d(size/2,-size/2,size/2);
                //glVertex3d(-size/2,-size/2,size/2);

                glColor3f(   0,  1.0, 0 );
                glVertex3d(-size/2,-size/2,-size/2);
                glVertex3d(-size/2,-size/2,+size/2);
                glVertex3d(-size/2,size/2,size/2);
                glVertex3d(-size/2,size/2,-size/2);
                //glVertex3d(-size/2,-size/2,-size/2);

                glColor3f(   0,  1.0, 0 );
                glVertex3d(size/2,-size/2,-size/2);
                glVertex3d(size/2,-size/2,+size/2);
                glVertex3d(size/2,size/2,size/2);
                glVertex3d(size/2,size/2,-size/2);
                //glVertex3d(size/2,-size/2,-size/2);

                glColor3f(   1.0,  0, 0 );
                glVertex3d(-size/2,-size/2,-size/2);
                glVertex3d(-size/2,-size/2,size/2);
                glVertex3d(size/2,-size/2,size/2);
                glVertex3d(size/2,-size/2,-size/2);
                //glVertex3d(-size/2,-size/2,-size/2);

                glColor3f(   1.0,  0, 0 );
                glVertex3d(-size/2,size/2,-size/2);
                glVertex3d(-size/2,size/2,size/2);
                glVertex3d(size/2,size/2,size/2);
                glVertex3d(size/2,size/2,-size/2);
                //glVertex3d(-size/2,size/2,-size/2);
                

                /*
        	glVertex3d(-size,0,size);
        	glVertex3d(size,0,size);
        	glVertex3d(size,0,-size);
        	glVertex3d(-size,0,-size);
        	glVertex3d(-size,size*2,-size);
        	glVertex3d(size,size*2,-size);
        	glVertex3d(size,size*2,size);
        	glVertex3d(-size,size*2,size);
                */
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