/*
 * The main entry point for all demos.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */
#include "include\gl\glut.h"

// Include the general application structure.
#include "app.h"
#include "dice_app.h"
// Include the timing functions
#include "timing.h"
#define NULL 0
// Forward declaration of the function that will return the
// application object for this particular demo. This should be
// implemented in the demo's .cpp file.
//extern Application* getApplication();

// Store the global application object.
DiceApp		*_diceApp;


/**
 * Creates a window in which to display the scene.
 */
void createWindow(const char* title)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,320);
    glutInitWindowPosition(0,0);
    glutCreateWindow(title);
}

/**
 * Called each frame to update the 3D scene. Delegates to
 * the application.
 */
void update()
{
    // Update the timing.
    TimingData::get().update();

    // Delegate to the application.
    _diceApp	-> update( );
}

/**
 * Called each frame to display the 3D scene. Delegates to
 * the application.
 */
void display()
{
	_diceApp	-> display( );

    // Update the displayed content.
    glFlush();
    glutSwapBuffers();
}

/**
 * Called when a mouse button is pressed. Delegates to the
 * application.
 */
void mouse(int button, int state, int x, int y)
{
	_diceApp	-> mouse( button, state, x, y );
}

/**
 * Called when the display window changes size.
 */
void reshape(int width, int height)
{
	_diceApp	-> resize( width, height );
}

/**
 * Called when a key is pressed.
 */
void keyboard(unsigned char key, int x, int y)
{
    // Note we omit passing on the x and y: they are rarely needed.
}

/**
 * Called when the mouse is dragged.
 */
void motion(int x, int y)
{
	_diceApp	-> mouseDrag( x, y );
}

/**
 * The main entry point. We pass arguments onto GLUT.
 */
void main(int argc, char** argv)
{
    // Set up GLUT and the timers
    glutInit(&argc, argv);
    TimingData::init();

    // Create the application and its window
	_diceApp	= new DiceApp( );
	_diceApp	-> initGraphics( );

    createWindow( _diceApp	-> getTitle( ) );

    // Set up the appropriate handler functions
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // Run the application
    glutMainLoop();

    // Clean up the application
    TimingData::deinit();
}