#include "Card.h"
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

Card::Card(void): mNumber( 0 ), mSuit( Card::SUIT_NONE ), mIsWin( false ), mPlace( Card::PLACE_DECK )
				, mOpen( false )
{
}

Card::~Card(void)
{
}

int Card::getNumber() const
{
	return mNumber;
}

void Card::setNumber( int n )
{
	assert( CARD_LOWNUMBER <= n && n <= CARD_HIGHNUMBER );

	mNumber = n;
}

Card::Suit Card::getSuit() const
{
	return mSuit;
}

void Card::setSuit( Suit s )
{
	mSuit = s;
}

void Card::reset()
{
	mIsWin = false;
	mPlace = PLACE_DECK;
	close();
}

bool Card::isWin() const
{
	return mIsWin;
}

void Card::win()
{
	mIsWin = true;
}

Card::Place Card::getPlace() const
{
	return mPlace;
}

void Card::setPlace( Place p )
{
	mPlace = p;
}

void Card::open()
{
	mOpen = true;
}

void Card::close()
{
	mOpen = false;
}

bool Card::isOpen() const
{
	return mOpen;
}

bool Card::operator>( const Card& a ) const
{
	return mNumber > a.mNumber;
}

bool Card::operator<( const Card& a ) const
{
	return mNumber < a.mNumber;
}

bool Card::operator==( const Card& a ) const
{
	return mNumber == a.mNumber;
}

bool Card::operator!=( const Card& a ) const
{
	return mNumber != a.mNumber;
}