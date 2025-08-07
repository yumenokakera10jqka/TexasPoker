#include "Player.h"
#include "CardPack.h"
#include "Decision.h"
#include "Card.h"
#include "Yaku.h"
#include "Action.h"
#include "MyMacro.h"
#include "Config.h"
#include <cassert>

using namespace std;

Player::Player(const string& name, CardPack* cp, Decision* ds ): mCardPack( cp ), mDecision( ds )
				, mName( name ), mWinCount( 0 ), mLoseCount( 0 ), mWinState( Player::STATE_NONE )
				, mChip( 0 ), mStackChip( 0 ), mBetChip( 0 ), mGainChip( 0 ), mChoice( Action::CHOICE_NONE ), mPosition( 0 )
				, mTurnState( TURN_YET ), mShowDown( false )
{
	assert( mCardPack != 0 );
	assert( mDecision != 0 );
	mDecision->setPlayer( this );
}

Player::~Player(void)
{
	SAFE_DELETE( mCardPack );
	SAFE_DELETE( mDecision );
}

void Player::initialize( const Config* con )
{
	mChip = con->getChipAmount(); 
	mTurnState = TURN_YET;
}

void Player::update( Action* action )
{
	mCardPack->updateYaku();
	const Yaku& yaku = mCardPack->getYaku();
	mDecision->decide( yaku, action );
}

void Player::setCard( Card* card )
{
	assert( card != 0 );
	mCardPack->setHand( card );
}

void Player::prepareGame()
{
	mCardPack->reset();
	mWinState = STATE_NONE;
	mChoice = Action::CHOICE_NONE;
	if( mTurnState != TURN_ELIMINATED )
	{
		mTurnState = TURN_YET;
	}
	mStackChip = 0;
	mGainChip = 0;
	mShowDown = false;
}

void Player::prepareRound()
{
	if( mChoice != Action::CHOICE_ALLIN
		&& mChoice != Action::CHOICE_FOLD )
	{
		mChoice = Action::CHOICE_NONE;
	}
	if( mTurnState == TURN_ACTIVE
		|| mTurnState == TURN_WAIT )
	{
		mTurnState = TURN_YET;
	}
	mDecision->prepareRound();
	mBetChip = 0;
}

string Player::getName() const
{
	return mName;
}

int Player::getChipAmount() const
{
	return mChip;
}

bool Player::stackChip( int amount )
{
	mStackChip += amount;
	mBetChip += amount;
	return true;
}

bool Player::popChip( int amount )
{
	assert( mStackChip >= amount );

	mStackChip -= amount;
	return true;
}

int Player::getStackChipAmount() const
{
	return mStackChip;
}

int Player::getBetChipAmount() const
{
	return mBetChip;
}

void Player::gainChip( int amount )
{
	mGainChip += amount;
}

int Player::getGainChipAmount() const
{
	return mGainChip;
}

bool Player::deposit( int amount )
{
	mChip += amount;
	return true;
}

bool Player::withDraw( int amount )
{
	if( mChip < amount )
	{
		return false;
	}
	mChip -= amount;
	return true;
}

void Player::setChoice( Action::Choice choice )
{
	mChoice = choice;
}

Action::Choice Player::getChoice() const
{
	return mChoice;
}

void Player::winGame()
{
	mWinCount++;
	mWinState = STATE_WIN;
	mCardPack->winGame();
}

void Player::loseGame()
{
	mLoseCount++;
	mWinState = STATE_LOSE;
}

void Player::showDown()
{
	if( mTurnState != TURN_OUT )
	{
		mShowDown = true;
		cardOpen();
		if( mTurnState == TURN_PASS )
		{
			mCardPack->updateYaku();
		}
	}
}

int Player::winCount() const
{
	return mWinCount;
}

int Player::loseCount() const
{
	return mLoseCount;
}

void Player::resetWinCount()
{
	mWinCount = 0;
	mLoseCount = 0;
}

bool Player::isWonThisGame() const
{
	return ( mWinState == STATE_WIN );
}

Player::WinState Player::getWinState() const
{
	return mWinState;
}

bool Player::operator>( const Player& p ) const
{
	if( mChoice == Action::CHOICE_FOLD )
	{
		return false;
	}
	if( p.mChoice == Action::CHOICE_FOLD )
	{
		return true;
	}
	return ( mCardPack->getYaku() ) > ( p.mCardPack->getYaku() );
}

bool Player::operator<( const Player& p ) const
{
	if( p.mChoice == Action::CHOICE_FOLD )
	{
		return false;
	}
	if( mChoice == Action::CHOICE_FOLD )
	{
		return true;
	}
	return ( mCardPack->getYaku() ) < ( p.mCardPack->getYaku() );
}

bool Player::operator==( const Player& p ) const
{
	if( mChoice == Action::CHOICE_FOLD && p.mChoice == Action::CHOICE_FOLD )
	{
		return true;
	}
	if( mChoice == Action::CHOICE_FOLD || p.mChoice == Action::CHOICE_FOLD )
	{
		return false;
	}
	return ( mCardPack->getYaku() ) == ( p.mCardPack->getYaku() );
}

void Player::setPosition( int pos )
{
	mPosition = pos;
}

int Player::getPosition() const
{
	return mPosition;
}

const Card& Player::getHand( int idx ) const
{
	return mCardPack->getHand( idx );
}

void Player::cardOpen()
{
	mCardPack->openHand();
}

int Player::getHandNum() const
{
	return mCardPack->getHandNum();
}

void Player::setTurnState( TurnState ts )
{
	mTurnState = ts;
}

Player::TurnState Player::getTurnState() const
{
	return mTurnState;
}

const Yaku& Player::getYaku() const
{
	return mCardPack->getYaku();
}

bool Player::isShowDown() const
{
	return mShowDown;
}
