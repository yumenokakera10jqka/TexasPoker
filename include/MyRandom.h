#pragma once

class RandomIf;

class MyRandom
{
public:
	static void set( RandomIf* );
	static void create();
	static void destroy();
	static RandomIf* instance();
	static int getRandom();

private:
	MyRandom();
	MyRandom( const MyRandom& );
	~MyRandom(void);

	static RandomIf* mInstance;
};
