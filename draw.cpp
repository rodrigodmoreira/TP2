#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "objloader.h"
#include "draw.h"

using namespace std;

enum LISTAS {BUILD01=0,ASPHALT,WALKWAY,POSTE,AP_BED,AP_BLUEBUTTON,AP_REDBUTTON,AP_LAMP,AP_COFFEE,AP_ELEVATOR,
                AP_KEYBOARD,AP_PILLOW,AP_SOFA,AP_PS4,AP_SERVERSIDE,AP_SERVERTOWER,AP_TAPETE,AP_WALL,AP_WIRE,AP_WOOD,AP_GLASS,AP_TOPHOUSE,
                MAIN_WINDOWS,MAIN_BODY,MAIN_LATERAL,MAIN_RING,MAIN_ELEVATOR,MAIN_GROUNDLIGHT,MAIN_LEAF,MAIN_WOOD,MAIN_VASE,MAIN_MESA,
                MAIN_TAPETE,MAIN_SOFA,MAIN_HALL_GENERIC,GROUND,AP_SERVERGLASS,SLAMP,CITY_LEAVES,CITY_TREES,CITY_GLASS};

void emissive(double alpha)
{
        GLfloat d[4] = {alpha,alpha,alpha,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d);
}

GLuint generateDisplayLists(ModelList modelList)
{
        GLuint inicio_lista = glGenLists(50); // numero objetos estáticos (um pouco maior na realidade)

        glNewList(inicio_lista+BUILD01, GL_COMPILE);   // Abre nova lista para compilar (guardar)
                glColor4f(.53,.73,.78,1);
                drawModel(0,-10,500,180,0,modelList.build01,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+ASPHALT, GL_COMPILE);
                glColor4f(.21,.24,.31,1);
                drawModel(0,-10,500,180,0,modelList.asphalt,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+WALKWAY, GL_COMPILE);
                glColor4f(.33,.39,.41,1);
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
                glColor4f(.17,.28,.29,1);
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
                glColor4f(.26,.42,.41,1);
                drawModel(0,-10,500,180,0,modelList.ap_pillow,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+AP_SOFA, GL_COMPILE);
                glColor4f(.84,.89,.75,1);
                drawModel(0,-10,500,180,0,modelList.ap_sofa,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_PS4, GL_COMPILE);
                glColor4f(.2,.2,.3,1);
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
                glColor4f(.50,.63,.42,1);
                drawModel(0,-10,500,180,0,modelList.ap_tapete,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_WALL, GL_COMPILE);
                glColor4f(.73,.81,.59,1);
                drawModel(0,-10,500,180,0,modelList.ap_wall,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_WIRE, GL_COMPILE);
                glColor4f(.43,.55,.35,1);
                drawModel(0,-9,500,180,0,modelList.ap_wire,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+AP_WOOD, GL_COMPILE);
                glColor4f(.13,.18,.31,1);
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
                emissive(.2);
                        glColor4f(.4,1,1,.3);
                        drawModel(0,-10,500,180,0,modelList.main_insidewindow,GLM_FLAT | GLM_MATERIAL);
                        drawModel(0,-10,500,180,0,modelList.main_window,GLM_FLAT | GLM_MATERIAL);
                emissive(0);
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
                glColor4f(.2,.7,.35,1);
                drawModel(0,-30,500,180,0,modelList.ground,GLM_FLAT | GLM_MATERIAL);
        glEndList();

        glNewList(inicio_lista+CITY_LEAVES, GL_COMPILE);
                glPushMatrix();
                        glScalef(1,.8,1);
                        glColor4f(.2,.7,.35,1);
                        drawModel(0,-10,500,180,0,modelList.city_leaves,GLM_FLAT | GLM_MATERIAL);
                glPopMatrix();
        glEndList();

        glNewList(inicio_lista+CITY_TREES, GL_COMPILE);
                glPushMatrix();
                        glScalef(1,.8,1);
                        glTranslatef(0,-5,0);
                        glColor4f(.6,.5,.45,1);
                        drawModel(0,-10,500,180,0,modelList.city_trees,GLM_FLAT | GLM_MATERIAL);
                glPopMatrix();
        glEndList();
        
        glNewList(inicio_lista+AP_SERVERGLASS, GL_COMPILE);
                glColor4f(.1,.8,.8,.3);
                drawModel(0,-10,500,180,0,modelList.ap_serverglass,GLM_FLAT | GLM_MATERIAL);
        glEndList();
        
        glNewList(inicio_lista+SLAMP, GL_COMPILE);
                glPushMatrix();
                        glScalef(1,2,1);        
                        emissive(.7);
                                glColor4f(.7,.6,64,.2);
                                drawModel(0,-10,500,180,0,modelList.sLamp,GLM_FLAT | GLM_MATERIAL);
                        emissive(0);
                glPopMatrix();
        glEndList();

        glNewList(inicio_lista+CITY_GLASS, GL_COMPILE);
                emissive(.2);
                        glColor4f(.4,1,1,.3);
                        drawModel(0,-10,500,180,0,modelList.city_glass,GLM_FLAT | GLM_MATERIAL);
                emissive(0);
        glEndList();

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

                glRotatef(increment,0,0,1);
                glRotatef(25,1,0,0);
                glTranslatef(0,1000000,0);
                
                emissive(.5);
                        glColor4f(1,1,0,1);
                        solMaterial();
                        glutSolidSphere(200000,10,10);
                emissive(.0);
        glPopMatrix();
}

void drawMoon(double increment)
{
        glPushMatrix();

                glRotatef(increment,0,0,1);
                glRotatef(25,1,0,0);
                glTranslatef(0,500000,0);
                
                emissive(.8);
                        glColor4f(.5,1,1,1);
                        solMaterial();
                        glutSolidSphere(50000,10,10);
                emissive(0);
        glPopMatrix();
}

void drawModel(double x,double y, double z, double degree, double sdegree, GLMmodel* model, GLuint shading)
{
        glPushMatrix();
                glTranslatef(x,y,z);
                glRotated(sdegree,0,0,1);
                glRotated(degree,0,1,0);
                glmDraw(model,shading);
        glPopMatrix();
}

void drawWireCube(double x,double y,double z,double size)
{
	size/=2;
	glPushMatrix();
	
                glTranslatef (x, y+size, z);
                glutWireCube (size);
	
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