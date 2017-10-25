#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "objloader.h"

using namespace std;

void solMaterial()
{
        GLfloat a[] = {1,1,1,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,a);
        GLfloat b[] = {1,1,1,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,b);
        GLfloat c[4] = {1,1,1,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,c);
        GLfloat d[4] = {.6,.6,.6,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d);
        GLfloat e[4] = {1,1,1,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,e);
}

void drawSun(double increment)
{
        glPushMatrix();

                glRotatef(increment/60,0,0,1);
                glRotatef(25,1,0,0);
                glTranslatef(0,1000000,0);
                glColor4f(1,1,0,1);
                solMaterial();
                glutSolidSphere(200000,10,10);
                
                {
                        GLfloat d[4] = {0,0,0,1};
                        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d);
                }
        glPopMatrix();
}

void drawModel(double x,double y, double z, double degree, double sdegree, GLMmodel* model, GLuint shading)
{
        glPushMatrix();
                glTranslatef(x,y,z);
                glRotated(sdegree,0,0,1);
                glRotated(degree,0,1,0);
                glmDraw(model,shading);
                // GLuint list = glmList(model,shading);
        glPopMatrix();

        // glCallLists(1, GL_UNSIGNED_BYTE, &list);
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
        
        GLdouble a[] = {0,-1,0};
        
        glBegin(GL_TRIANGLE_FAN);
                glNormal3dv(a);
        	glVertex3d(-size,0,-size);
        	glVertex3d(size,0,-size);
        	glVertex3d(size,0,size);
        	glVertex3d(-size,0,size);
        glEnd();
	
	glPopMatrix();
}

void drawSolidCube(double x,double y,double z,double vdegree,double hdegree,double size)
{
        glPushMatrix();
                glTranslated(x,y,z);
                glRotated(1,0,0,vdegree);
                glRotated(0,1,0,hdegree);

                glutSolidCube(size);
        glPopMatrix();
}