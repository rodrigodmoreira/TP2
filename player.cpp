#include <cmath>
#include "player.h"

using namespace std;

void Camera::groundLimit()
{
	this->maxlimit={5050,0,5780,1};
	this->minlimit={-5050,0,-4660,1};
}

void Camera::apLimit()
{
	this->maxlimit={140,0,1160,1};
	this->minlimit={-140,0,465,1};
}

void Camera::walkFoward()
{
	double nx = this->eye.x+this->spd*sin(this->degree*M_PI/180)*this->hspd,
			nz = this->eye.z+this->spd*cos(this->degree*M_PI/180)*this->hspd;

	// Checagem para verificar se atingiu a borda 
	// e impede a movimentação apenas no eixo e no sentido daquele movimento, assim, é possível andar pra trás
	if(this->maxlimit.x>nx && this->minlimit.x<nx)
		this->eye.x=nx;
	if(this->maxlimit.z>nz && this->minlimit.z<nz)
		this->eye.z=nz;
}

void Camera::walkBackward()
{
	double nx = this->eye.x-this->spd*sin(this->degree*M_PI/180)*this->hspd,
			nz = this->eye.z-this->spd*cos(this->degree*M_PI/180)*this->hspd;

	if(this->maxlimit.x>nx && this->minlimit.x<nx)
		this->eye.x=nx;
	if(this->maxlimit.z>nz && this->minlimit.z<nz)
		this->eye.z=nz;
}

void Camera::walkSideR()
{
	double nx = this->eye.x-this->spd*sin((this->degree+90)*M_PI/180)*this->hspd,
			nz =this->eye.z-this->spd*cos((this->degree+90)*M_PI/180)*this->hspd;

	if(this->maxlimit.x>nx && this->minlimit.x<nx)
		this->eye.x=nx;
	if(this->maxlimit.z>nz && this->minlimit.z<nz)
		this->eye.z=nz;
}

void Camera::walkSideL()
{
	double nx = this->eye.x+this->spd*sin((this->degree+90)*M_PI/180)*this->hspd,
			nz = this->eye.z+this->spd*cos((this->degree+90)*M_PI/180)*this->hspd;

	if(this->maxlimit.x>nx && this->minlimit.x<nx)
		this->eye.x=nx;
	if(this->maxlimit.z>nz && this->minlimit.z<nz)
		this->eye.z=nz;
}