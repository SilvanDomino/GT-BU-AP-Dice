#ifndef DICE_APP
#define DICE_APP

#include "TableTop.h"
#include "dice.h"
#include "include\cyclone\cyclone.h"
#include "include\cyclone\core.h"
class DiceApp : public Application
{
private:
	TableTop *_tableTop;
public:
	DiceApp( );
	~DiceApp( );
	GameDie *_dice;
	virtual void display( );
	virtual void update( );	
	virtual const char *getTitle( );
	
	void mouse( int button, int state, int x, int y );
	void mouseDrag( int x, int y );	
};

#endif