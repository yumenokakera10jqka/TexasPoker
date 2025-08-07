#include "Action.h"
#include "Player.h"
#include "Bet.h"
#include "MyMacro.h"
#include <cassert>

#ifndef TEST_ACTION
	#define FUNC_COLLECT collect
	#define FUNC_BET bet
	#define FUNC_RAISE raise
	#define FUNC_CALL call
	#define FUNC_CHECK check
	#define FUNC_FOLD fold
	#define FUNC_ALLIN allIn
	#define FUNC_LITTLEBLIND littleBlind
	#define FUNC_BIGBLIND bigBlind
	#define FUNC_ISPOSSIBLELITTLEBLIND isPossibleLittleBlind
	#define FUNC_ISPOSSIBLEBIGBLIND isPossibleBigBlind
	#define FUNC_ISPOSSIBLEBET isPossibleBet
	#define FUNC_ISPOSSIBLERAISE isPossibleRaise
	#define FUNC_ISPOSSIBLECHECK isPossibleCheck
	#define FUNC_ISPOSSIBLECALL isPossibleCall
	#define FUNC_ISPOSSIBLEFOLD isPossibleFold
	#define FUNC_ISPOSSIBLEALLIN isPossibleAllIn
#endif

using namespace std;

Action::Action( Bet* bet ): mBet( bet ), mStackChip( 0 )
{
	mBet->setAction( this );
	resetPossible();
}

Action::~Action(void)
{
	SAFE_DELETE( mBet );
}

void Action::prepareGame()
{
	mBet->prepareGame();
	mStackChip = 0;
}

void Action::prepareRound()
{
	mBet->prepareRound();
}

void Action::action( Action::Choice choice, Player* player )
{
	assert( isPossible( choice) );

	switch( choice )
	{
	case CHOICE_BET:
		FUNC_BET( player );
		break;
	case CHOICE_RAISE:
		FUNC_RAISE( player );
		break;
	case CHOICE_CALL:
		FUNC_CALL( player );
		break;
	case CHOICE_CHECK:
		FUNC_CHECK( player );
		break;
	case CHOICE_FOLD:
		FUNC_FOLD( player );
		break;
	case CHOICE_ALLIN:
		FUNC_ALLIN( player );
		break;
	case CHOICE_LITTLEBLIND:
		FUNC_LITTLEBLIND( player );
		break;
	case CHOICE_BIGBLIND:
		FUNC_BIGBLIND( player );
		break;
	};
}

void Action::collect( Player* player, int amount )
{
	assert( haveChip( player, amount ) );

	player->withDraw( amount );
	player->stackChip( amount );
}

bool Action::isPossible( Action::Choice choice ) const
{
	return mPossible[choice];
}

void Action::setPossible( Player* player )
{
	resetPossible();

	// リトルブラインド可能の場合、他のアクションは全て不可能
	if( FUNC_ISPOSSIBLELITTLEBLIND( player ) )
	{
		mPossible[Action::CHOICE_LITTLEBLIND] = true;
		return;
	}
	// ビッグブラインド可能の場合、他のアクションは全て不可能
	if( FUNC_ISPOSSIBLEBIGBLIND( player ) )
	{
		mPossible[Action::CHOICE_BIGBLIND] = true;
		return;
	}
	mPossible[Action::CHOICE_BET] = FUNC_ISPOSSIBLEBET( player );
	mPossible[Action::CHOICE_RAISE] = FUNC_ISPOSSIBLERAISE( player );
	mPossible[Action::CHOICE_CHECK] = FUNC_ISPOSSIBLECHECK( player );
	mPossible[Action::CHOICE_CALL] = FUNC_ISPOSSIBLECALL( player );
	mPossible[Action::CHOICE_FOLD] = FUNC_ISPOSSIBLEFOLD( player );
	mPossible[Action::CHOICE_ALLIN] = FUNC_ISPOSSIBLEALLIN( player );
}

int Action::getCurrentBet() const
{
	return mBet->getBet();
}

int Action::getBet() const
{
	return mBet->getBetOrg();
}

int Action::getStackChipAmount() const
{
	return mStackChip;
}

void Action::bet( Player* player )
{
	mBet->bet( player );
	mStackChip = player->getStackChipAmount();
}

void Action::raise( Player* player )
{
	mBet->raise( player );
	mStackChip = player->getStackChipAmount();
}

void Action::check( Player* player )
{
	player->setChoice( Action::CHOICE_CHECK );
}

void Action::call( Player* player )
{
	int stackDiff = mStackChip - player->getStackChipAmount();

	FUNC_COLLECT( player, stackDiff );
	
	player->setChoice( CHOICE_CALL );
}

void Action::fold( Player* player )
{
	player->setChoice( CHOICE_FOLD );
}

void Action::littleBlind( Player* player )
{
	mBet->littleBlind( player );
}

void Action::bigBlind( Player* player )
{
	mStackChip = mBet->bigBlind( player );
}

void Action::allIn( Player* player )
{
	FUNC_COLLECT( player, player->getChipAmount() );
	player->setChoice( CHOICE_ALLIN );
}

void Action::resetPossible()
{
	for( int i = 0; i < CHOICE_NONE; i++ )
	{
		mPossible[i] = false;
	}
}

bool Action::isPossibleBet( Player* player ) const
{
	return mBet->isPossibleBet( player );
}

bool Action::isPossibleRaise( Player* player ) const
{
	return mBet->isPossibleRaise( player );
}

bool Action::isPossibleCheck( Player* player ) const
{
	return ( player->getStackChipAmount() == mStackChip );
}

bool Action::isPossibleCall( Player* player ) const
{
	if( haveStackChip( player ) )
	{
		return ( player->getStackChipAmount() < mStackChip );
	}
	return false;
}

bool Action::isPossibleAllIn( Player* player ) const
{
	return !( haveStackChip( player ) );
}

bool Action::isPossibleLittleBlind( Player* player ) const
{
	return mBet->isPossibleLittleBlind( player );
}

bool Action::isPossibleBigBlind( Player* player ) const
{
	return mBet->isPossibleBigBlind( player );
}

bool Action::isPossibleFold( Player* player ) const
{
	return true;
}

bool Action::haveStackChip( Player* player ) const
{
	assert( mStackChip >= player->getStackChipAmount() );

	int push =  mStackChip - player->getStackChipAmount();
	
	return ( player->getChipAmount() >= push );
}

bool Action::haveChip( Player* player, int amount ) const
{
	return ( player->getChipAmount() >= amount );
}
