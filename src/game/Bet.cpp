#include "Bet.h"
#include "Player.h"
#include "Action.h"
#include <cassert>

using namespace std;

Bet::Bet( int betOrg ): mAction( 0 ), mBetOrg( betOrg ), mBet( betOrg ), mBeted( false )
						, mLittleBlinded( false ), mBigBlinded( false )
{
}

Bet::~Bet(void)
{
}

void Bet::setAction( Action* ac )
{
	mAction = ac;
}

void Bet::prepareGame()
{
	mBet = mBetOrg;
	mBeted =false;
	mLittleBlinded = false;
	mBigBlinded = false;
}

void Bet::prepareRound()
{
	mBeted =false;
	mBet = mBetOrg;
}

void Bet::bet( Player* player )
{
	mAction->collect( player, mBet );
	player->setChoice( Action::CHOICE_BET );
	mBeted = true;
	mBet = calcNextBet();
}

void Bet::raise( Player* player )
{
	mAction->collect( player, mBet );
	player->setChoice( Action::CHOICE_RAISE );
	mBet = calcNextBet();
}

int Bet::bigBlind( Player* player )
{
	mBigBlinded = true;
	player->setChoice( Action::CHOICE_BIGBLIND );
	mBeted = true;
	mAction->collect( player, mBetOrg );
	mBet = calcNextBet();

	return mBetOrg;
}

int Bet::littleBlind( Player* player )
{
	mLittleBlinded = true;
	int bet = calcLittleBlindAmount();
	mAction->collect( player, bet );
	player->setChoice( Action::CHOICE_LITTLEBLIND );

	return bet;
}

bool Bet::isPossibleBet( Player* player ) const
{
	if( mAction->haveChip( player, mBet ) )
	{
		return !mBeted;
	}
	return false;
}

bool Bet::isPossibleRaise( Player* player ) const
{
	if( mAction->haveChip( player, mBet ) )
	{
		return mBeted;
	}
	return false;
}

bool Bet::isPossibleLittleBlind( Player* player ) const
{
	if( calcLittleBlindAmount() <= player->getChipAmount() )
	{
		return !mLittleBlinded;
	}
	return false;
}

bool Bet::isPossibleBigBlind( Player* player ) const
{
	if( mBetOrg <= player->getChipAmount() )
	{
		return ( mLittleBlinded && !mBigBlinded );
	}
	return false;
}

int Bet::getBet() const
{
	return mBet;
}

int Bet::getBetOrg() const
{
	return mBetOrg;
}

int Bet::calcNextBet() const
{
	return mBet * 2;
}

int Bet::calcLittleBlindAmount() const
{
	return ( mBet >> 1 );
}