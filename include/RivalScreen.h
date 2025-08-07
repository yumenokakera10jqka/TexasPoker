#pragma once
#include "ScreenOperator.h"
#include "PlayerMediator.h"

//class Screen;
class FlexScreen;

class RivalScreen :
	public ScreenOperator
{

friend class RivalScreenTest;

public:
	RivalScreen();
	~RivalScreen(void);

	void draw( View::ViewState );

private:
	void createScreen();
	void clear();
	void update( View::ViewState );
	void drawHeader();
//	void updateRow( int row, PlayerMediator::PlayerValue );

	FlexScreen* mScreen;
/*
	Screen* mScreen1;
	Screen* mScreen2;
	Screen* mScreen3;
	*/
};
