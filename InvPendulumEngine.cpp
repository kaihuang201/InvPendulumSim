#include "InvPendulumEngine.h"
#include <cmath>

InvPendulumEngine::InvPendulumEngine()
{
    //ctor
	this->time_step = 0.050; //50 ms

    this->pen_len = 1.0;
    this->pen_mass = 1.0;
    this->pen_angle = 0.0;
	this->pen_angular_vel = 0.0;
    this->cart_mass = 10.0;
    this->cart_pos = 0.0;
    this->cart_vel = 0.0;

	this->force = 0.0;
	this->nextForce = 0.0;

	this->gravity = 9.81;

	this->step_im = EULER;
}

InvPendulumEngine::~InvPendulumEngine()
{
    //dtor
}

InvPendulumEngine::InvPendulumEngine(const InvPendulumEngine& other)
{
    //copy ctor
}

InvPendulumEngine& InvPendulumEngine::operator=(const InvPendulumEngine& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void InvPendulumEngine::step()
{
	//Stuff...

	//Update the physics
	//Call the correct function based on the chosen integration method
	switch(this->step_im)
	{
	case EULER:
		this->UpdatePhysicsEuler();
		break;
	case RK4:
		this->UpdatePhysicsRK4();
		break;
	default:
		//Default to Euler
		this->UpdatePhysicsEuler();
		break;
	}

	this->force = this->nextForce;
	this->nextForce = 0;

	//Stuff...
}

void InvPendulumEngine::UpdatePhysicsEuler()
{
	//Rename variables to match pdf
	double m=this->pen_mass;
	double M=this->cart_mass;
	double L=this->pen_len;
	double g=this->gravity;
	double dt=this->time_step;
	double x1=this->cart_pos, x2=this->cart_vel, x3=this->pen_angle, x4=this->pen_angular_vel;
	double u = this->force;

	//Create temporary variable to hold new values without overwriting old ones
	double new_cart_pos=0.0, new_cart_vel=0.0, new_pen_angle=0.0, new_pen_omega=0.0;

	// Euler integration
	new_cart_pos = x1 + dt*x2;
	new_cart_vel = x2 + dt*( (m*g*sin(x3)*cos(x3) - m*L*sqr(x4)*sin(x3)-u) / (m*sqr(cos(x3)) - (M+m)) );
	new_pen_angle = x3 + dt*x4;
	new_pen_omega = x4 + dt*( (-1.0*(M+m)*g*sin(x3) + m*L*sqr(x4)*sin(x3)*cos(x3) + u*cos(x3)) / (m*L*sqr(cos(x3))-(M+m)*L) );

	//Update the simulation's state variables with the new, calculated values
	this->pen_angle = new_pen_angle;
	this->pen_angular_vel = new_pen_omega;
	this->cart_pos = new_cart_pos;
	this->cart_vel = new_cart_vel;
}

void InvPendulumEngine::UpdatePhysicsRK4()
{
	//TODO

	//Right now, since RK4 isn't implemented yet, just pass into Euler update
	//Ideally, this function won't be called until RK4 is implemented
	this->UpdatePhysicsEuler();
}