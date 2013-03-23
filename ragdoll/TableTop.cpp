#include <cstdlib>
#include <iostream>
#include "include\cyclone\cyclone.h"
#include "stdafx.h"
#include "TableTop.h"
#include "app.h"
//#include 
//#define ROD_COUNT 15
TableTop :: TableTop( ) : RigidBodyApplication( )
{	
	//generateContacts( );
}

void TableTop :: generateContacts( )
{
	this -> _collisionPlane = new CollisionPlane( );
	this -> _tableJoint		= new Joint( );
	this -> cData			= CollisionData( );
	this -> cData.contacts	= new Contact[this -> maxContacts];

	this -> _collisionPlane -> direction	= Vector3( 0, 1, 0 );	//planes normal
	this -> _collisionPlane -> offset		= 0.0f;					//the dist from the plane to the origin.

	this -> cData.reset( this -> maxContacts );
	this -> cData.friction		= 0.5f;
	this -> cData.restitution	= 0.5f;
	this -> cData.tolerance		= 0.0f;

	this -> cData.addContacts( this -> _tableJoint -> addContact( this -> cData.contacts, this -> cData.contactsLeft ) );
	
}

void TableTop :: update( )
{
	
}

void TableTop :: updateObjects( cyclone::real duration )
{

}

void TableTop :: reset( )
{

}

void TableTop :: display( )
{	
	glBegin( GL_POLYGON );

	//draw a number of squares to represent the tabletop.
	for ( unsigned i = 0; i < 10; i ++ )
	{
		float size = i * 10;
		glVertex3f( i, 0, i );
	}

	glEnd( );
}

void reset( )
{

}

TableTop :: ~TableTop( )
{
	//if (  )
}
