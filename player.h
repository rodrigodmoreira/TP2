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
		double degree;
		double bob;
		Ponto eye;

	Camera()
	{
		this->spd=.1;
		this->degree=0;
		this->bob=0;
		this->eye={0,0,0,1}; // Posição no mundo
	}
};
// reservate names

#endif // PLAYER_H