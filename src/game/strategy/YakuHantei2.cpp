#include "YakuHantei2.h"
#include <cassert>

#ifndef TEST_YAKUHANTEI2

	#define FUNC_RESET reset

#endif

using namespace std;

YakuHantei2::YakuHantei2(void): mIsSet( false ), mCards( YAKUHANTEI2_CARDNUM )
{
}

YakuHantei2::~YakuHantei2(void)
{
}

int YakuHantei2::numInCharge() const
{
	return YAKUHANTEI2_CARDNUM;
}

void YakuHantei2::setCards( Card** srcCards )
{
	assert( srcCards != 0 );

	FUNC_RESET();

	for( int i = 0; i < YAKUHANTEI2_CARDNUM; i++ )
	{
		assert( srcCards[i] != 0 );

		mCards.add( srcCards[i] );
	}

	mIsSet = true;
}

bool YakuHantei2::hantei()
{
	if( !mIsSet ){ return false; }

	// ワンペア
	if( *mCards[0] == *mCards[1] )
	{
		mYaku.setYaku( Yaku::YAKU_ONEPAIR );
		for( int i = 0; i < YAKUHANTEI2_CARDNUM; i++ )
		{
			mYaku.addYakuCard( mCards[i] );
		}
		return true;
	}

	// ハイカード
	mYaku.setYaku( Yaku::YAKU_HIGHCARD );
	for( int i = 0; i < YAKUHANTEI2_CARDNUM; i++ )
	{
		mYaku.addNotYakuCard( mCards[i] );
	}

	return false;
}

const Yaku& YakuHantei2::getYaku() const
{
	return mYaku;
}

void YakuHantei2::reset()
{
	mIsSet = false;
	mCards.reset();
	mYaku.reset();
}
