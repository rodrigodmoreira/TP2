#include <cmath>
#include "player.h"

using namespace std;

void Camera::walkFoward()
{
	this->eye.x+=this->spd*sin(this->degree*M_PI/180);
	this->eye.z+=this->spd*cos(this->degree*M_PI/180);
}

void Camera::walkBackward()
{
	this->eye.x-=this->spd*sin(this->degree*M_PI/180);
	this->eye.z-=this->spd*cos(this->degree*M_PI/180);
}

void Camera::walkSideR()
{
	this->eye.x-=this->spd*sin((this->degree+90)*M_PI/180);
	this->eye.z-=this->spd*cos((this->degree+90)*M_PI/180);
}

void Camera::walkSideL()
{
	this->eye.x+=this->spd*sin((this->degree+90)*M_PI/180);
	this->eye.z+=this->spd*cos((this->degree+90)*M_PI/180);
}