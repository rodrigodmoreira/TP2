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
		double ground;	// altura do chão do jogador (para diferenciar térreo do andar do apartamento)
		double degree;	// angulo horizontal de movimentação da cabeça
		double vdegree;	// angulo vertical de movimentação da cabeça
		double bob;	// angulo correspondente ao sacudir da cabeça
		double mousesense;	// constante para movimento linear do mouse
		double fov;
		bool running;	// is running
		int mode;	// camera mode
		int canWarp;
		Ponto eye;
		Ponto maxlimit;
		Ponto minlimit;
		Ponto mlast; // mouse last position
		std::string display_text;

	void groundLimit(); // Configura borda no chão
	void apLimit();	// configura borda no apartamento

	Camera()
	{
		this->fov=65.0;
		this->mode=1;
		this->spd=0;
		this->height=2;
		this->ground=0;
		this->vspd=0;
		this->hspd=0;
		this->degree=0;
		this->vdegree=0;
		this->bob=0;
		this->running=false;
		this->eye={0,0,0,1}; // Posição no mundo
		this->mlast={0,0,0,1};
		this->mousesense=1;
		this->display_text="";
		this->canWarp=0;
		this->groundLimit();
	}

	void walkFoward();
	void walkBackward();
	void walkSideR();
	void walkSideL();
};
// reservate names

#endif // PLAYER_H