#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "objloader.h"
#include "draw.h"

using namespace std;

enum LISTAS {BUILD01=0,ASPHALT,WALKWAY,POSTE,AP_BED,AP_BLUEBUTTON,AP_REDBUTTON,AP_LAMP,AP_COFFEE,AP_ELEVATOR,
                AP_KEYBOARD,AP_PILLOW,AP_PS4,AP_SERVERSIDE,AP_SERVERTOWER,AP_TAPETE,AP_WALL,AP_WIRE,AP_WOOD,AP_GLASS,AP_TOPHOUSE,
                MAIN_WINDOWS,MAIN_BODY,MAIN_LATERAL,MAIN_RING,MAIN_ELEVATOR,MAIN_GROUNDLIGHT,MAIN_LEAF,MAIN_WOOD,MAIN_VASE,MAIN_MESA,
                MAIN_TAPETE,MAIN_SOFA,MAIN_HALL_GENERIC,GROUND,AP_SERVERGLASS,SLAMP};

void emissive(double alpha)
{
        GLfloat d[4] = {alpha,alpha,alpha,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d);
}

GLuint generateDisplayLists(ModelList modelList)
{
        GLuint inicio_lista = glGenLists(41); // 41 objetos estáticos até o momento

        glNewList(inicio_lista+BUILD01, GL_COMPILE);   // Abre nova lista para compilar (guardar)
                glColor4f(1,1,1,1);
                drawModel(0,-10,500,180,0,modelList.build01,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+ASPHALT, GL_COMPILE);
                glColor4f(.3,.3,.3,1);
                drawModel(0,-10,500,180,0,modelList.asphalt,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+WALKWAY, GL_COMPILE);
                glColor4f(.4,.4,.4,1);
                drawModel(0,-10,500,180,0,modelList.walkway,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+POSTE, GL_COMPILE);
                glPushMatrix();
                        glScalef(1,2,1);
                        glColor4f(1,1,1,1);
                        drawModel(0,-10,500,180,0,modelList.poste,GLM_FLAT | GLM_MATERIAL);
                glPopMatrix();
        glEndList();

        glNewList(inicio_lista+AP_BED, GL_COMPILE);
                glColor4f(.63,.41,.84,1);
                drawModel(0,-10,500,180,0,modelList.ap_bed,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+AP_BLUEBUTTON, GL_COMPILE);
                glColor4f(.1,.1,1,1);
                drawModel(0,-20,500,180,0,modelList.ap_bluebutton,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_REDBUTTON, GL_COMPILE);
                glColor4f(1,.1,.1,1);
                drawModel(0,-20,500,180,0,modelList.ap_redbutton,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_LAMP, GL_COMPILE);
                glColor4f(.6,1,1,1);
                drawModel(0,-10,500,180,0,modelList.ap_lamp,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_COFFEE, GL_COMPILE);
                glColor4f(.7,.7,.8,1);
                drawModel(0,-10,500,180,0,modelList.ap_coffee,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_ELEVATOR, GL_COMPILE);
                glColor4f(.3,.3,.3,1);
                drawModel(0,-10,500,180,0,modelList.ap_elevator,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_KEYBOARD, GL_COMPILE);
                glColor4f(.5,.5,.5,1);
                drawModel(0,-10,500,180,0,modelList.ap_keyboard,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_PILLOW, GL_COMPILE);
                glColor4f(1,1,1,1);
                drawModel(0,-10,500,180,0,modelList.ap_pillow,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_PS4, GL_COMPILE);
                glColor4f(.4,.4,.4,1);
                drawModel(0,-10,500,180,0,modelList.ap_ps4,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_SERVERSIDE, GL_COMPILE);
                glColor4f(.3,.3,.3,1);
                drawModel(0,-20,500,180,0,modelList.ap_serverside,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_SERVERTOWER, GL_COMPILE);
                glColor4f(.6,.6,.6,1);
                drawModel(0,-20,500,180,0,modelList.ap_servertower,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_TAPETE, GL_COMPILE);
                glColor4f(.2,.1,.9,1);
                drawModel(0,-10,500,180,0,modelList.ap_tapete,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_WALL, GL_COMPILE);
                glColor4f(1,.98,.25,1);
                drawModel(0,-10,500,180,0,modelList.ap_wall,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_WIRE, GL_COMPILE);
                glColor4f(1,.6,.14,1);
                drawModel(0,-9,500,180,0,modelList.ap_wire,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_WOOD, GL_COMPILE);
                glColor4f(.96,.88,.64,1);
                drawModel(0,-10,500,180,0,modelList.ap_wood,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_GLASS, GL_COMPILE);
                glColor4f(.1,.8,.8,.3);
                drawModel(0,-10,500,180,0,modelList.ap_glass,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_TOPHOUSE, GL_COMPILE);
                glColor4f(.1,.1,.1,1);
                drawModel(0,-10,500,180,0,modelList.ap_tophouse,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_WINDOWS, GL_COMPILE);
                glColor4f(.4,1,1,.5);
                drawModel(0,-10,500,180,0,modelList.main_insidewindow,GLM_FLAT | GLM_MATERIAL);
                drawModel(0,-10,500,180,0,modelList.main_window,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_BODY, GL_COMPILE);
                glColor4f(.2,.2,.2,1);
                drawModel(0,-10,500,180,0,modelList.main_body,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_LATERAL, GL_COMPILE);
                glColor4f(.2,.2,.2,1);
                drawModel(0,-10,500,180,0,modelList.main_lateral,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_RING, GL_COMPILE);
                glColor4f(.3,.3,.3,1);
                drawModel(0,-10,500,180,0,modelList.main_ring,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_ELEVATOR, GL_COMPILE);
                glColor4f(.5,.5,.5,1);
                drawModel(0,-10,500,180,0,modelList.main_elevator,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_GROUNDLIGHT, GL_COMPILE);
                glColor4f(1,1,1,1);
                drawModel(0,-10,500,180,0,modelList.main_groundlight,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_LEAF, GL_COMPILE);
                glColor4f(.1,.7,.3,1);
                drawModel(0,-10,500,180,0,modelList.main_leaf,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_WOOD, GL_COMPILE);
                glColor4f(.8,.4,.2,1);
                drawModel(0,-10,500,180,0,modelList.main_wood,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_VASE, GL_COMPILE);
                glColor4f(.6,.2,.1,1);
                drawModel(0,-10,500,180,0,modelList.main_vase,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_MESA, GL_COMPILE);
                glColor4f(.8,.7,.6,1);
                drawModel(0,-10,500,180,0,modelList.main_mesa,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_TAPETE, GL_COMPILE);
                glColor4f(.5,.5,.5,1);
                drawModel(0,-10,500,180,0,modelList.main_tapete,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_SOFA, GL_COMPILE);
                glColor4f(1,1,1,1);
                drawModel(0,-10,500,180,0,modelList.main_sofa,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+MAIN_HALL_GENERIC, GL_COMPILE);
                glColor4f(.95,.13,.19,1);
                drawModel(0,-10,500,180,0,modelList.main_hall_generic,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+GROUND, GL_COMPILE);
                glColor4f(.2,.7,.1,1);
                drawModel(0,-10,500,180,0,modelList.ground,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_SERVERGLASS, GL_COMPILE);
                glColor4f(.1,.8,.8,.3);
                drawModel(0,-10,500,180,0,modelList.ap_serverglass,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+SLAMP, GL_COMPILE);
                glPushMatrix();
                        glScalef(1,2,1);        
                        emissive(.4);
                                glColor4f(.7,.6,.5,.3);
                                drawModel(0,-10,500,180,0,modelList.sLamp,GLM_FLAT | GLM_MATERIAL);
                glPopMatrix();
        glEndList();
        
        // glNewList(inicio_lista, GL_COMPILE);
        // glEndList();
        
        // glNewList(inicio_lista, GL_COMPILE);
        // glEndList();
        
        // glNewList(inicio_lista, GL_COMPILE);
        // glEndList();
        
        // glNewList(inicio_lista, GL_COMPILE);
        // glEndList();        

        return inicio_lista;
}

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