#ifndef BASIC_DIC
#define BASIC_DIC

#include <cstdlib>
#include <iostream>
#include "include\cyclone\cyclone.h"
#include "stdafx.h"
#include "app.h"
#include "include\gl\glut.h"

using namespace cyclone;

class BasicDice : public RigidBodyApplication
{
public:
	RigidBody * vertices;
	BasicDice( );
	~BasicDice( );

	void Display();
	void InputHandler();

};


#endif