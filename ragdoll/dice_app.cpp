#include "dice_app.h"
#include "include\cyclone\cyclone.h"
#include "stdafx.h"
#include "BasicDice.h"
#include "dice.h"

DiceApp :: DiceApp( ) : Application( )
{	
	_tableTop = new TableTop( );
	_dice = new GameDie();
}

DiceApp :: ~DiceApp( )
{
	if ( _tableTop )	delete _tableTop;
	if ( _dice )	delete _dice;
}

void DiceApp :: display( )
{
	glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glVertex2i(1, 1);
    glVertex2i(639, 319);
    glEnd();

	//draw scale liness
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.75, 0.75, 0.75);
    for (unsigned i = 1; i < 20; i++)
    {
        glBegin(GL_LINE_LOOP);
        for (unsigned j = 0; j < 32; j++)
        {
            float theta = 3.1415926f * j / 16.0f;
            glVertex3f(i*cosf(theta),0.0f,i*sinf(theta));
        }
        glEnd();
    }
    glBegin(GL_LINES);
    glVertex3f(-20,0,0);
    glVertex3f(20,0,0);
    glVertex3f(0,0,-20);
    glVertex3f(0,0,20);
    glEnd();
	
	_tableTop	-> display( );
	_dice -> display();
}

void DiceApp :: update( )
{
	_tableTop	-> update( );	
	_dice->update();
}

const char *DiceApp :: getTitle( )
{
	return "Jur en Silvan's epic dice project";
}

void DiceApp :: mouse( int button, int state, int x, int y )
{
	//_tableTop	-> mouse( button, state, x, y );
}

void DiceApp :: mouseDrag( int x, int y )
{
//	_tableTop	-> mouseDrag( x, y );
}