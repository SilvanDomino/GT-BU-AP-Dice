#ifndef TABLE_TOP
#define TABLE_TOP

#include <cstdlib>
#include <iostream>
#include "include\cyclone\cyclone.h"
#include "include\gl\glut.h"
#include "stdafx.h"
#include "app.h"
#include "include\cyclone\joints.h"
#include "timing.h"
using namespace cyclone;

class TableTop// : public RigidBodyApplication
{
private:
	CollisionPlane	*_collisionPlane;
	Joint			*_tableJoint;
	
public:
	TableTop( );
	~TableTop( );

	virtual void generateContacts( );

	virtual void update( );

	virtual void display( );

	virtual void updateObjects( cyclone :: real duration );

	virtual void reset( );
};

#endif