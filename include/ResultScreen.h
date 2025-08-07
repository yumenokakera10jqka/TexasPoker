#pragma once
#include "ScreenOperator.h"

class Screen;

class ResultScreen :
	public ScreenOperator
{

friend class ResultScreenTest;

public:
	ResultScreen();
	~ResultScreen(void);

	void draw( View::ViewState );

private:
	void createScreen();
	void clear();
	void update();
	void update( View::ViewState );

	Screen* mScreen;
};
