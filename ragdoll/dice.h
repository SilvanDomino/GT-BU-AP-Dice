#ifndef DICE_THING
#define DICE_THING
class GameDie : public RigidBodyApplication
{   
protected:
	int _numberOfSides;	//D6, D8, etc.
	RigidBody * vertices;
public:
    /** Creates a new demo object. */
    GameDie();
    virtual ~GameDie( );
	
	void updateAdditionalMass();
    /** Returns the window title for the demo. */
    virtual const char* getTitle( );

    /** Display the particles. */
    virtual void display( );

    /** Update the particle positions. */
    virtual void update( );

    /** Handle a key press. */
    virtual void key( unsigned char key );

	virtual void mouse( int button, int state, int x, int y );

	virtual void mouseDrag( int x, int y );

	virtual void generateContacts( );

	virtual void updateObjects( cyclone :: real duration );
	virtual void reset( );
};
#endif