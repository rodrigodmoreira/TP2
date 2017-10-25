#ifndef  DRAW_H // <- Prevents multiple inclusions
#define DRAW_H // <- ...

#include "objloader.h"

/**************************/
// your stuff goes here
// function prototypes, etc.
void drawSun(double increment);
void drawModel(double x,double y, double z,double degree, double sdegree, GLMmodel* model, GLuint shading);
void drawWireCube(double x,double y,double z,double size);
void drawSolidCube(double x,double y,double z,double vdegree,double hdegree,double size);
void drawPlane(double x,double y, double z, double size);
// classes
// reservate names

#endif // DRAW_H