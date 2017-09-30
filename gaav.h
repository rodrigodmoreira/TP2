#ifndef  GAAV_H // <- Prevents multiple inclusions
#define GAAV_H // <- ...

#include <stdio.h>

/**************************/
// your stuff goes here
// function prototypes, etc.
// classes
class Vetor
{
	public:
		
		double x,y,z,w;
		
		Vetor()
		{
			this->x=0;
			this->y=0;
			this->z=0;
			this->w=0;
		}

		Vetor(double x,double y, double z, double w)
		{
			this->x=x;
			this->y=y;
			this->z=z;
			this->w=w;
			if(this->w==1)
				printf("GAAV error(vetor)\n");	
		}
};
class Ponto
{
	public:

		double x,y,z,w;
		
		Ponto()
		{
			this->x=0;
			this->y=0;
			this->z=0;
			this->w=1;
		}

		Ponto(double x,double y, double z, double w)
		{
			this->x=x;
			this->y=y;
			this->z=z;
			this->w=w;
			if(this->w==0)
				printf("GAAV error(ponto)\n");	
		}
};

Vetor multiplicaPorEscalar(Vetor v, double alpha);
Vetor somaVetorComVetor(Vetor v, Vetor u);
Vetor diferencaVetorComVetor(Vetor v, Vetor u);
Vetor diferencaEntrePontos(Ponto p, Ponto q);
Ponto somaPontoComVetor(Ponto p, Vetor v);
double normaDoVetor(Vetor v);
Vetor normalizado(Vetor v);
double distanciaEntrePontos(Ponto p, Ponto q);
double produtoEscalar(Vetor v, Vetor u);
Vetor produtoVetorial(Vetor v, Vetor u);
double anguloEntreVetores(Vetor v, Vetor u);
Ponto combinacaoAfim2Pontos(Ponto p, Ponto q, double alpha);
// reservate names

#endif // GAAV_H