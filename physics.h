#ifndef  PHYSICS_H // <- Prevents multiple inclusions
#define PHYSICS_H // <- ...

#include "player.h"

/**************************/
// your stuff goes here
// function prototypes, etc.
void calculatePhysics(int* keyState,Camera &cam,Ponto *p,double increment);
double from0toX(double x,double defasamento,double spd,double increment); // sobrecarga de método
// classes
// reservate names

#endif // PHYSICS_H