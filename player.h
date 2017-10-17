#ifndef  PLAYER_H // <- Prevents multiple inclusions
#define PLAYER_H // <- ...

#include <string>
#include "gaav.h"

/**************************/
// your stuff goes here
// function prototypes, etc.
// classes
class Camera
{
	public:

		double spd;	// velocidade maxima
		double hspd,vspd;	//  suavizar transição de movimento (parado->andando/ andando->parado)(acelarção e fricção)
		double height;
		double degree;
		double vdegree;
		double bob;
		double mousesense;
		bool running;
		int mode;
		Ponto eye;
		Ponto mlast; // mouse last position
		std::string display_text;

	Camera()
	{
		this->mode=0;
		this->spd=1;
		this->height=2;
		this->vspd=0;
		this->hspd=0;
		this->degree=0;
		this->vdegree=0;
		this->bob=0;
		this->running=false;
		this->eye={0,0,0,1}; // Posição no mundo
		this->mlast={0,0,0,1};
		this->mousesense=1.8;
		this->display_text="";
	}

	void walkFoward();
	void walkBackward();
	void walkSideR();
	void walkSideL();
};
// reservate names

#endif // PLAYER_H