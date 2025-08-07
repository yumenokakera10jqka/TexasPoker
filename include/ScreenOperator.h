#pragma once
#include "View.h"

class ScreenOperator
{
public:
	ScreenOperator(void){};
	virtual ~ScreenOperator(void){};

	virtual void draw( View::ViewState ) = 0;
};
