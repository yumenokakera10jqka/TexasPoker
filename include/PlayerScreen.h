#pragma once
#include "ScreenOperator.h"
#include "PlayerMediator.h"

//class Screen;
class FlexScreen;

class PlayerScreen :
	public ScreenOperator
{

friend class PlayerScreenTest;

public:
	PlayerScreen();
	~PlayerScreen(void);

	void draw( View::ViewState );

private:
	void createScreen();
	void clear();
	void drawHeader();
	void update( View::ViewState );
//	void updateRow( int row, PlayerMediator::PlayerValue );
	void updateActionCol();
	void getInput();

	FlexScreen* mScreen;
//	Screen* mScreen;
};
