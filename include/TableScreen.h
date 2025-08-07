#pragma once
#include "ScreenOperator.h"

//class Screen;
class FlexScreen;

class TableScreen :
	public ScreenOperator
{

friend class TableScreenTest;

public:
	TableScreen();
	~TableScreen(void);

	void draw( View::ViewState );

private:
	void createScreen();
	void clear();
	void update( View::ViewState );
	void drawHeader();

	FlexScreen* mScreen;
	//Screen* mScreen;
};
