/*
 * The dice demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <iostream>
#include "include\gl\glut.h"
#include "include\cyclone\cyclone.h"
#include "app.h"
#include "TableTop.h"
#include "timing.h"
#include <stdio.h>
#include <cassert>
#include "dice.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define VECTOR			cyclone :: Vector3
#define RIGID_BODY		cyclone :: RigidBody
/**
 * The main demo class definition.
 */
using namespace cyclone;



// Method definitions
GameDie :: GameDie()
{
	float size = 4;
	vertices = new RigidBody[48];
	Vector3 pointO = Vector3(0,0,0);
	for(int i = 0; i < 8; i++){			//y axis
		vertices[i].setPosition(	size*0.5,		sin((float)0.25 * i * M_PI) * size,		cos((float)0.25 * i * M_PI)* size		);
		vertices[i+8].setPosition(	-size*0.5,		sin((float)0.25 * i * M_PI) * size,		cos((float)0.25 * i * M_PI)* size		);
		vertices[i+16].setPosition(	sin((float)0.25 * i * M_PI) * size,		size*0.5 ,		cos((float)0.25 * i * M_PI)* size	);
		vertices[i+24].setPosition(	sin((float)0.25 * i * M_PI) * size,		-size*0.5 ,		cos((float)0.25 * i * M_PI)* size		);
		vertices[i+32].setPosition(	sin((float)0.25 * i * M_PI) * size,		cos((float)0.25 * i * M_PI)* size,	size*0.5		);
		vertices[i+40].setPosition(	sin((float)0.25 * i * M_PI) * size,		cos((float)0.25 * i * M_PI)* size, -size*0.5		);
	}
	
	for(int i = 0; i < 48; i++){
		vertices[i].setMass(1);
		vertices[i].setVelocity(8,0,0);
		vertices[i].setAcceleration(Vector3::GRAVITY);
	}
}

GameDie :: ~GameDie( )
{
	
}

void GameDie :: updateAdditionalMass( )
{
   
}

void GameDie :: display( )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RigidBodyApplication :: display( );

	
	glColor3f(0.5f, 0,0);
	for(int i = 0; i < 36; i++){
		Vector3 pos = vertices[i].getPosition();
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glutSolidSphere(0.25f, 20, 10);
        glPopMatrix();
	}
	glBegin(GL_LINES);
	glColor3f(1, 0.5f,0);
	
	for(int i = 0; i < 48; i++){
		Vector3 *p1 = &vertices[i].getPosition();
		Vector3 *p2 = &vertices[i+1].getPosition();
		glPushMatrix();
		glVertex3f(p1->x, p1->y, p1->z);
		glVertex3f(p2->x, p2->y, p2->z);
		glPopMatrix();
	}
	glEnd();
}

void GameDie :: update( )
{
    RigidBodyApplication :: update( );
	for(int i = 0; i < 48; i++){
		vertices[i].clearAccumulators();
		vertices[i].calculateDerivedData();
	}
    updateAdditionalMass();
}

const char* GameDie :: getTitle( )
{
    return "SILVAN =D dice example";
}

void GameDie :: key( unsigned char key )
{
	
}

void GameDie :: mouse( int button, int state, int x, int y )
{

}

void GameDie :: mouseDrag( int x, int y )
{
	
}

void GameDie :: generateContacts( )
{

}

void GameDie :: updateObjects( cyclone :: real duration )
{

}

void GameDie :: reset( )
{

}
