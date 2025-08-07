#include "IRandom.h"
#include <ctime>
#include <cstdlib>

using namespace std;

IRandom::IRandom(void)
{
	srand((unsigned)time(NULL));
}

IRandom::~IRandom(void)
{
}

int IRandom::getRandom()
{
	return rand();
}
