#include "PlayerMediator.h"
#include "Player.h"
#include "WordConverter.h"
#include "VValue.h"
#include "Card.h"
#include <string>
#include <cassert>

PlayerMediator* PlayerMediator::mInstance = 0;

using namespace std;

PlayerMediator::PlayerMediator(void): mPlayerNum( 0 ), mSelectedPlayer( PLAYER_NONE ), mCurrentPlayer( 0 )
{
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mPlayers[i] = 0;
	}
}

PlayerMediator::~PlayerMediator(void)
{
}

void PlayerMediator::create()
{
	if( mInstance ) return;

	mInstance = new PlayerMediator();
} 

void PlayerMediator::destroy()
{
	if( mInstance ) delete( mInstance );
	mInstance = 0;
}

PlayerMediator* PlayerMediator::instance()
{
	return mInstance;
}

void PlayerMediator::addRefObject( Player* p )
{
	assert( mPlayerNum < PLAYER_MAX );
	mPlayers[mPlayerNum++] = p;
}

void PlayerMediator::selectPlayer( PlayerIdx pIdx )
{
	mSelectedPlayer = pIdx;
	mCurrentPlayer = (int)pIdx;
}

bool PlayerMediator::next()
{
	// ŽŸ‚ÌƒvƒŒƒCƒ„[‚ª‚¢‚é‚Ì‚Í‚b‚o‚t‚Ì‚Ý
	if( mSelectedPlayer == PLAYER_MAN
		|| mSelectedPlayer == PLAYER_NONE )
	{
		return false;
	}
	// ––”ö‚Ì‚b‚o‚t‚ª‚·‚Å‚É‘I‘ð‚³‚ê‚Ä‚¢‚éê‡
	if( mCurrentPlayer == mPlayerNum - 1 )
	{
		return false;
	}
	mCurrentPlayer++;
	return true;
}

int PlayerMediator::getPlayerNum() const
{
	return mPlayerNum;
}

VValueSet PlayerMediator::getValue( PlayerValue pValue ) const
{
	string rValue = "";
	Player* p = mPlayers[mCurrentPlayer];

	VValueSet atSet;
	VValue at;

	switch( pValue )
	{
	case PLAYER_NAME:
		at.setValue( p->getName() );
		atSet.addVValue(at);
		break;
	case PLAYER_CHIP:
		at.setValue( WordConverter::toString( p->getChipAmount() ) );
		atSet.addVValue( at );
		break;
	case PLAYER_STACKCHIP:
		at.setValue( WordConverter::toString( p->getBetChipAmount() ) );
		atSet.addVValue( at );
		break;
	case PLAYER_ACTION:
		at.setValue( WordConverter::convertChoice( p ) );
		atSet.addVValue( at );
		break;
	case PLAYER_ACTIVE:
		at.setValue( WordConverter::convertTurnState( p ) );
		at.setColor( WordConverter::getTurnStateColor( p ) );
		atSet.addVValue( at );
		break;
	case PLAYER_WIN:
		at.setValue(  WordConverter::convertWinState( p )  );
		atSet.addVValue( at );
		break;
	case PLAYER_HAND:
		for( int i = 0; i < p->getHandNum(); i++ )
		{
			const Card& card = p->getHand( i );
			at.clear();
			at.setValue( WordConverter::convertCard( card ) );
			at.setColor( WordConverter::getSuitColor( card ) );
			if( p->isShowDown() && card.isWin() )
			{
				at.getFormat()->mDeco = Format::DECO_SHARP;
			}
			atSet.addVValue( at );
		}
		break;
	case PLAYER_YAKU:
		at.setValue(  WordConverter::convertYaku( p )  );
		atSet.addVValue( at );
		break;
	}

	return atSet;
}

