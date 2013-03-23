/*
 * The bridge demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <gl/glut.h>
#include <cyclone/cyclone.h>
#include "../app.h"
#include "../timing.h"

#include <stdio.h>
#include <cassert>

#define PARTICLE_COUNT 16
#define ROD_COUNT 16
#define BUNGEE_COUNT 3

#define BASE_MASS 1
#define EXTRA_MASS 10
#define VECTOR cyclone::Vector3
/**
 * The main demo class definition.
 */
class BridgeDemo : public MassAggregateApplication
{
    cyclone::ParticleRod *rods;
	VECTOR base1, base2, base3;
	cyclone::ParticleRod *topRods;
	cyclone::ParticleCableConstraint *cables;
	cyclone::ParticleAnchoredBungee *bungees;
	cyclone::ParticleAnchoredSpring *springs;

    /**
     * Updates particle masses to take into account the mass
     * that's crossing the bridge.
     */
    void updateAdditionalMass();

public:
    /** Creates a new demo object. */
    BridgeDemo();
    virtual ~BridgeDemo();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particles. */
    virtual void display();

    /** Update the particle positions. */
    virtual void update();

    /** Handle a key press. */
    virtual void key(unsigned char key);
};

// Method definitions
BridgeDemo::BridgeDemo()
:
MassAggregateApplication(PARTICLE_COUNT), rods(0), cables(0), springs(0), topRods(0)
{
	base1 = VECTOR(-1.5,7.5,0);
	base2 = VECTOR(0, 7.5,0);
	base3 = VECTOR(1.5, 7.5,0);
    // Create the masses and connections.
	particleArray[0].setPosition(base1);	//top left
	particleArray[1].setPosition(base2);	//top mid
	particleArray[2].setPosition(base3);  //top right

	particleArray[3].setPosition(0,5.5,0);	//top head
	particleArray[4].setPosition(0,4.9,0);	//lower head
	particleArray[5].setPosition(0,4.5,0);	//neck

	particleArray[6].setPosition(-1.5, 4.7,0);	//left shoulder
	particleArray[7].setPosition(-1.5, 4.3,0);
	particleArray[8].setPosition(-2.5, 2,0);	//left hand

	particleArray[9].setPosition(1.5, 4.7,0);	//right shoulder
	particleArray[10].setPosition(1.5, 4.3,0);
	particleArray[11].setPosition(2.5, 2,0);	//right hand

	particleArray[12].setPosition(-1.5, 1.5,0);	//left hip
	particleArray[13].setPosition(1.5, 1.5,0);	//right hip

	particleArray[14].setPosition(-1.5, -3,0);	//left leg
	particleArray[15].setPosition(1.5, -3,0);	//right leg
    for (unsigned i = 0; i < PARTICLE_COUNT; i++)
    {
        particleArray[i].setVelocity(0,0,0);
        particleArray[i].setDamping(0.9f);
		if(i > 2) particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
        particleArray[i].clearAccumulator();
    }
	
	topRods = new cyclone::ParticleRod[3];
	topRods[0].particle[0] = &particleArray[0]; //top head
	topRods[0].particle[1] = &particleArray[1];
	topRods[0].length = 1.5;
	topRods[1].particle[0] = &particleArray[1]; //top head
	topRods[1].particle[1] = &particleArray[2];
	topRods[1].length = 1.5;
	topRods[2].particle[0] = &particleArray[2]; //top head
	topRods[2].particle[1] = &particleArray[0];
	topRods[2].length = 3;
	for (unsigned i = 0; i < 3; i++)
    {
		world.getContactGenerators().push_back(&topRods[i]);
	}
	/*
	cyclone::ParticleSpring springsa = cyclone::ParticleSpring(&particleArray[0], 1, 2);
	cyclone::ParticleSpring springsb = cyclone::ParticleSpring(&particleArray[1], 1, 1);
	cyclone::ParticleSpring springsc = cyclone::ParticleSpring(&particleArray[2], 1, 2);
	world.getForceRegistry().add(&particleArray[6], &springsa);
	world.getForceRegistry().add(&particleArray[3], &springsb);
	world.getForceRegistry().add(&particleArray[9], &springsc);
	
	
	springs = new cyclone::ParticleAnchoredSpring[3];
	springs[0] = cyclone::ParticleSpring(&particleArray[0], 1, 2);
	springs[1] = cyclone::ParticleSpring(&particleArray[1],1,1);
	springs[2] = cyclone::ParticleAnchoredSpring(&particleArray[2],1,2);

	world.getForceRegistry().add(&particleArray[6], &springs[0]);
	world.getForceRegistry().add(&particleArray[3], &springs[1]);
	world.getForceRegistry().add(&particleArray[9], &springs[2]);*/
	
	cables = new cyclone::ParticleCableConstraint[3];
	cables[0].anchor = particleArray[0].getPosition();
	cables[0].particle = &particleArray[6];
	cables[0].maxLength = 2;
	cables[1].anchor = particleArray[1].getPosition();
	cables[1].particle = &particleArray[3];
	cables[1].maxLength = 1;
	cables[2].anchor = particleArray[2].getPosition();
	cables[2].particle = &particleArray[9];
	cables[2].maxLength = 2;
	for (unsigned i = 0; i < 3; i++)
    {
		cables[i].restitution = 0.5f;
		world.getContactGenerators().push_back(&cables[i]);
	}

	/*		//just weird
	bungees = new cyclone::ParticleAnchoredBungee[BUNGEE_COUNT];
	bungees[0].init(&particleArray[0].getPosition(), 0, 3);
	bungees[1].init(&particleArray[1].getPosition(), 0, 2);
	bungees[2].init(&particleArray[2].getPosition(), 0, 3);
	world.getForceRegistry().add(&particleArray[6], &bungees[0]);
	world.getForceRegistry().add(&particleArray[3], &bungees[1]);
	world.getForceRegistry().add(&particleArray[9], &bungees[2]);*/

    rods = new cyclone::ParticleRod[ROD_COUNT];
	rods[0].particle[0] = &particleArray[3]; //top head
	rods[0].particle[1] = &particleArray[4];
	rods[0].length = 1;
	rods[1].particle[0] = &particleArray[4]; //neck
	rods[1].particle[1] = &particleArray[5];
	rods[1].length = 0.5;
	rods[15].particle[0] = &particleArray[7]; //mid torso
	rods[15].particle[1] = &particleArray[10];
	rods[15].length = 2;
	rods[2].particle[0] = &particleArray[5]; //left torso
	rods[2].particle[1] = &particleArray[7];
	rods[2].length = 1.1;
	rods[3].particle[0] = &particleArray[6]; //left shoulder
	rods[3].particle[1] = &particleArray[7];
	rods[3].length = 0.5;
	rods[4].particle[0] = &particleArray[6]; //left arm
	rods[4].particle[1] = &particleArray[8];
	rods[4].length = 3.4;
	rods[5].particle[0] = &particleArray[7]; //left arm
	rods[5].particle[1] = &particleArray[8];
	rods[5].length = 3;
	rods[6].particle[0] = &particleArray[5]; //right torso
	rods[6].particle[1] = &particleArray[10];
	rods[6].length = 1.1;
	rods[7].particle[0] = &particleArray[10]; //right shoulder
	rods[7].particle[1] = &particleArray[9];
	rods[7].length = 0.5;
	rods[8].particle[0] = &particleArray[9]; //right arm
	rods[8].particle[1] = &particleArray[11];
	rods[8].length = 3.4;
	rods[9].particle[0] = &particleArray[10]; //right arm
	rods[9].particle[1] = &particleArray[11];
	rods[9].length = 3;
	rods[10].particle[0] = &particleArray[7]; //left body
	rods[10].particle[1] = &particleArray[12];
	rods[10].length = 3.5;
	rods[11].particle[0] = &particleArray[10]; //right body
	rods[11].particle[1] = &particleArray[13];
	rods[11].length = 3.5;
	rods[12].particle[0] = &particleArray[12]; //penis area
	rods[12].particle[1] = &particleArray[13];
	rods[12].length = 2;
	rods[13].particle[0] = &particleArray[12]; //left leg
	rods[13].particle[1] = &particleArray[14];
	rods[13].length = 2;
	rods[14].particle[0] = &particleArray[13]; //right leg
	rods[14].particle[1] = &particleArray[15];
	rods[14].length = 2;
	for (unsigned i = 0; i < ROD_COUNT; i++)
    {
		world.getContactGenerators().push_back(&rods[i]);
	}
    updateAdditionalMass();
}

BridgeDemo::~BridgeDemo()
{
    if (cables) delete[] cables;
    if (rods) delete[] rods;
}

void BridgeDemo::updateAdditionalMass()
{
    for (unsigned i = 0; i < PARTICLE_COUNT; i++)
    {
        particleArray[i].setMass(BASE_MASS);
    }
}

void BridgeDemo::display()
{
    MassAggregateApplication::display();

    glBegin(GL_LINES);
    glColor3f(0,0,1);
	
    for (unsigned i = 0; i < ROD_COUNT; i++)
    {
        cyclone::Particle **particles = rods[i].particle;
        const cyclone::Vector3 &p0 = particles[0]->getPosition();
        const cyclone::Vector3 &p1 = particles[1]->getPosition();
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }
	glColor3f(1,0,0.2);
	glVertex3f(particleArray[0].getPosition().x, particleArray[0].getPosition().y, particleArray[0].getPosition().z);
	glVertex3f(particleArray[6].getPosition().x, particleArray[6].getPosition().y, particleArray[6].getPosition().z);
	glVertex3f(particleArray[1].getPosition().x, particleArray[1].getPosition().y, particleArray[1].getPosition().z);
	glVertex3f(particleArray[3].getPosition().x, particleArray[3].getPosition().y, particleArray[3].getPosition().z);
	glVertex3f(particleArray[2].getPosition().x, particleArray[2].getPosition().y, particleArray[2].getPosition().z);
	glVertex3f(particleArray[9].getPosition().x, particleArray[9].getPosition().y, particleArray[9].getPosition().z);


    glEnd();

    glPushMatrix();
    glPopMatrix();

}

void BridgeDemo::update()
{
    MassAggregateApplication::update();
    updateAdditionalMass();
	for(int i = 0; i < 3; i++){
		if(particleArray[i].getPosition().y > 8){
			particleArray[0].setVelocity(0, 0,0);
			particleArray[1].setVelocity(0, 0,0);
			particleArray[2].setVelocity(0, 0,0);
			if(i ==0) particleArray[0].setPosition(base1);
			if(i ==1) particleArray[1].setPosition(base2);
			if(i ==2) particleArray[2].setPosition(base3);
		}
		if(particleArray[i].getPosition().y < 7.4){
			particleArray[0].setVelocity(0, 0,0);
			particleArray[1].setVelocity(0, 0,0);
			particleArray[2].setVelocity(0, 0,0);
			particleArray[0].setPosition(base1);
			particleArray[1].setPosition(base2);
			particleArray[2].setPosition(base3);
			particleArray[0].setVelocity(0, 0,0);
			particleArray[1].setVelocity(0, 0,0);
			particleArray[2].setVelocity(0, 0,0);
		}
	}
}

const char* BridgeDemo::getTitle()
{
    return "Cyclone > Bridge Demo";
}

void BridgeDemo::key(unsigned char key)
{
    switch(key)
    {
    case 's': case 'S':
		particleArray[1].setVelocity(0, 1,0);
		printf("ads");
        break;
	case 'a': case 'A':
		particleArray[0].setVelocity(0, 1,0);
        break;
	case 'd': case 'D':
		particleArray[2].setVelocity(0, 1,0);

        break;

    default:
        MassAggregateApplication::key(key);
    }
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
    return new BridgeDemo();
}