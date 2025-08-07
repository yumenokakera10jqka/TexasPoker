#include "CardManager.h"
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

CardManager::CardManager(void): mTop( 0 )
{
	srand((unsigned)time(NULL));
}

CardManager::~CardManager(void)
{
}

void CardManager::initialize()
{
	int pos = 0;

	for( int i = 0; i < CARD_SUITNUM; i++ )
	{
		for( int j = CARD_LOWNUMBER; j <= CARD_HIGHNUMBER; j++ )
		{
			mCardsO[pos].setNumber( j );
			mCardsO[pos].setSuit( (Card::Suit)i );
			mCards[pos] = &mCardsO[pos];
			pos++;
		}
	}
}

void CardManager::reset()
{
	for( int i = 0; i < CARDMANAGER_CARDNUM; i++ )
	{
		mCardsO[i].reset();
	}
}

void CardManager::shuffle()
{
	mTop = 0;

	int left = 0;
	int right = CARDMANAGER_CARDNUM - 1;
	int select = 0;
	Card* tmp = 0;

	while( left < right )
	{
		select = left + rand() % ( right - left + 1 );
		tmp = mCards[select];
		mCards[select] = mCards[right];
		mCards[right] = tmp;
		--right;
	}
}

Card* CardManager::take()
{
	assert( mTop < CARDMANAGER_CARDNUM );
	return mCards[mTop++];
}

const Card& CardManager::takeR( int pos ) const
{
	assert( 0 <= pos && pos < CARDMANAGER_CARDNUM );
	return *mCards[pos];

}
