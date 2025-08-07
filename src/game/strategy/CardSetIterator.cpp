#include "CardSetIterator.h"
#include "Card.h"
#include <cassert>
#include <string.h>	//memcpy_s

#define first(n) ((combi) ((1U << (n)) - 1U))

using namespace std;

CardSetIterator::CardSetIterator( int selectNum ): mCardNum( 0 ), mSelectNum( selectNum )
								, mCombi( 0 )
{
	for( int i = 0; i < CARDSET_MAX; i++ )
	{
		mCards[i] = 0;
	}

	for( int i = 0; i < CARDSET_MAX; i++ )
	{
		mCardSet[i] = 0;
	}

	mCombi = first( mSelectNum );
}

CardSetIterator::CardSetIterator( const CardSetIterator& a )
{
	*this = a;
}

CardSetIterator::~CardSetIterator(void)
{
}

void CardSetIterator::setCard( Card* cd )
{
	assert( mCardNum < CARDSET_MAX );

	mCards[mCardNum++] = cd;
}

Card** CardSetIterator::getNextSet()
{
	assert(  mSelectNum <= mCardNum );

	if(! ( mCombi & ~first( mCardNum )))
	{
		combi tmp = mCombi;

		int pos = 0;	// 選択されたカードの挿入位置
		int notSelectPos = mSelectNum;	// 選択されなかったカードの挿入位置

		for( int i = 0; i < mCardNum; i++ )
		{
			if( 1 & tmp )
			{
				assert( pos < mSelectNum );
				mCardSet[pos++] = mCards[i];
			}
			else
			{
				assert( notSelectPos < mCardNum );
				mCardSet[notSelectPos++] = mCards[i]; 

			}
			tmp >>= 1;
		}

		assert( pos == mSelectNum );
		assert( notSelectPos == mCardNum );

		combi smallest, ripple, new_smallest, ones;

		// 次の組み合わせに更新する
		smallest = mCombi & -(int)mCombi;
		ripple = mCombi + smallest;
		new_smallest = ripple & -(int)ripple;
		ones = ((new_smallest / smallest) >> 1) - 1;
		mCombi = ripple | ones;

		return mCardSet;
	}

	return 0;
}

int CardSetIterator::getCardNum() const
{
	return mCardNum;
}

int CardSetIterator::getSelectNum() const
{
	return mSelectNum;
}

CardSetIterator& CardSetIterator::operator=( const CardSetIterator& a )
{
	mCardNum = a.mCardNum;
	mSelectNum = a.mSelectNum;
	mCombi = a.mCombi;

	memcpy_s( mCards, sizeof( Card* ) * CARDSET_MAX
		, a.mCards, sizeof( Card* ) * CARDSET_MAX );

	memcpy_s( mCardSet, sizeof( Card* ) * CARDSET_MAX
		, a.mCardSet, sizeof( Card* ) * CARDSET_MAX );

	return *this;
}
