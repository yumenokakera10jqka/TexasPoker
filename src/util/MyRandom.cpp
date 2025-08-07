#include "MyRandom.h"
#include "IRandom.h"
#include <cassert>

using namespace std;

RandomIf* MyRandom::mInstance = 0;

MyRandom::MyRandom(void)
{
}

MyRandom::~MyRandom(void)
{
}

RandomIf* MyRandom::instance()
{
	if( mInstance == 0 )
	{
		create();
	}
	return mInstance;
}

int MyRandom::getRandom()
{
	if( mInstance == 0 )
	{
		create();
	}
	return mInstance->getRandom();
}

void MyRandom::set( RandomIf* r )
{
	if( mInstance )
	{
		destroy();
	}
	mInstance = r;
}

void MyRandom::create()
{
	if( mInstance == 0 )
	{
		mInstance = new IRandom();
	}
}

void MyRandom::destroy(void)
{
	delete( mInstance );
	mInstance = 0;
}
