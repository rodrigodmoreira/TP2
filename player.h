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
		double vdegree;
		double bob;
		double mousesense;
		int mode;
		Ponto eye;
		Ponto mlast; // mouse last position

	Camera()
	{
		this->mode=0;
		this->spd=1;
		this->degree=0;
		this->vdegree=0;
		this->bob=0;
		this->eye={0,0,0,1}; // Posição no mundo
		this->mlast={0,0,0,1};
		this->mousesense=1.8;
	}

	void walkFoward();
	void walkBackward();
	void walkSideR();
	void walkSideL();
};
// reservate names

#endif // PLAYER_H