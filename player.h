#ifndef  PLAYER_H // <- Prevents multiple inclusions
#define PLAYER_H // <- ...

#include "gaav.h"

/**************************/
// your stuff goes here
// function prototypes, etc.
// classes
class Camera
{
	public:

		double spd;
		double theta;
		Ponto eye;
		Vetor dir;
		Vetor up;

	Camera()
	{
		this->spd=.1;
		this->theta=0;
		this->eye={0,0,0,1}; // Posição no mundo
		this->dir={0,0,-1,0}; // Começa olhando pra frente
		this->up={0,1,0,0};
	}
};
// reservate names

#endif // PLAYER_H