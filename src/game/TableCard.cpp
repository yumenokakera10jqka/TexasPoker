#include "TableCard.h"
#include "Card.h"
#include <cassert>

using namespace std;

TableCard::TableCard(void): mCardNum( 0 ), mShowDown( false )
{
	for( int i = 0; i < TABLECARD_MAX; i++ )
	{
		mCards[i] = 0;
	}
}

TableCard::~TableCard(void)
{
}

void TableCard::setCard( Card* c )
{
	assert( mCardNum < TABLECARD_MAX );

	c->setPlace( Card::PLACE_TABLE );	//TODO:ƒeƒXƒg
	c->open();
	mCards[mCardNum++] = c;
}

const Card& TableCard::get( int i ) const
{
	assert( 0 <= i && i < mCardNum );

	return *mCards[i];
}

void TableCard::getCards( Card** cards, int size )
{
	assert( 0 <= size && size <= mCardNum );

	for( int i = 0; i < size; i++ )
	{
		cards[i] = mCards[i];
	}
}

void TableCard::reset()
{
	mCardNum = 0;
	for( int i = 0; i < TABLECARD_MAX; i++ )
	{
		mCards[i] = 0;
	}
	mShowDown = false;
}

int TableCard::getCardNum() const
{
	return mCardNum;
}

void TableCard::showDown()
{
	mShowDown = true;
}

bool TableCard::isShowDown() const
{
	return mShowDown;
}
