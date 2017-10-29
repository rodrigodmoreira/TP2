#ifndef  DRAW_H // <- Prevents multiple inclusions
#define DRAW_H // <- ...

#include "objloader.h"

/**************************/
// your stuff goes here
typedef struct ModelList{
	GLMmodel* build01;
	GLMmodel* asphalt;
	GLMmodel* walkway;
	GLMmodel* torre;
	GLMmodel* aura;
	GLMmodel* main_body;
	GLMmodel* main_window;
	GLMmodel* main_insidewindow;
	GLMmodel* main_ring;
	GLMmodel* main_lateral;
	GLMmodel* main_hall_generic;
	GLMmodel* main_bot;
	GLMmodel* main_elevator;
	GLMmodel* main_groundlight;
	GLMmodel* main_leaf;
	GLMmodel* main_wood;
	GLMmodel* main_vase;
	GLMmodel* main_mesa;
	GLMmodel* main_tapete;
	GLMmodel* main_sofa;
	GLMmodel* main_hdoor;
	GLMmodel* ap_bed;
	GLMmodel* ap_bluebutton;
	GLMmodel* ap_coffee;
	GLMmodel* ap_elevator;
	GLMmodel* ap_elevatorglass;
	GLMmodel* ap_glass;
	GLMmodel* ap_homeroom_monitor;
	GLMmodel* ap_keyboard;
	GLMmodel* ap_lamp;
	GLMmodel* ap_pillow;
	GLMmodel* ap_sofa;
	GLMmodel* ap_ps4;
	GLMmodel* ap_redbutton;
	GLMmodel* ap_serverglass;
	GLMmodel* ap_serverside;
	GLMmodel* ap_servertower;
	GLMmodel* ap_superpc;
	GLMmodel* ap_tapete;
	GLMmodel* ap_tophouse;
	GLMmodel* ap_wall;
	GLMmodel* ap_white;
	GLMmodel* ap_wire;
	GLMmodel* ap_wood;
	GLMmodel* ground;
	GLMmodel* cloud;
	GLMmodel* poste;
	GLMmodel* sLamp;
	GLMmodel* airplane;
	GLMmodel* city_trees;
	GLMmodel* city_leaves;
	GLMmodel* city_glass;
} ModelList;
// function prototypes, etc.
void drawSun(double increment);
void drawMoon(double increment);
void drawModel(double x,double y, double z,double degree, double sdegree, GLMmodel* model, GLuint shading);
void drawWireCube(double x,double y,double z,double size);
void drawSolidCube(double x,double y,double z,double vdegree,double hdegree,double size);
void drawPlane(double x,double y, double z, double size);
void emissive(double alpha);
GLuint generateDisplayLists(ModelList modelList);
// classes
// reservate names

#endif // DRAW_H