#pragma once
#include "RandomIf.h"

class IRandom : public RandomIf
{
public:
	IRandom(void);
	~IRandom(void);

	int getRandom();

};
