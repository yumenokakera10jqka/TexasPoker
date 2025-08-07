#include "stdafx.h"
#include "GameMain.h"
#include "Config.h"
#include "GameBuilder.h"
#include "View.h"
#include "Dealer.h"
#include "Sequence.h"
#include "MyMacro.h"
#include <cassert>

using namespace std;

GameMain::GameMain(void): mConfig( 0 ), mGameBuilder( 0 ), mView( 0 ), mSequence( 0 )
						, mState( ST_STARTMENU ), mMoveTo( ST_NONE )
{
}

GameMain::~GameMain(void)
{
	SAFE_DELETE( mSequence );
	SAFE_DELETE( mView );
	SAFE_DELETE( mGameBuilder );
	SAFE_DELETE( mConfig );
}

void GameMain::gameStart( void )
{
	bool isContinue = true;

	while( isContinue )
	{
		switch( mState )
		{
		case ST_STARTMENU:
			mState = startMenu();
				break;
		case ST_PLAY:
			mState = play();
				break;
		case ST_EXIT:
			isContinue = false;
				break;
		}
	}
}

void GameMain::gameInitialize( void )
{
	mGameBuilder->getDealer()->initialize( mConfig );
}

void GameMain::moveTo( State st )
{
	assert( mMoveTo = ST_NONE );
	mMoveTo = st;
}

GameMain::State GameMain::startMenu()
{
	mConfig = new Config();
	mConfig->startMenu();
	mGameBuilder = new GameBuilder( mConfig );
	Dealer* dealer = mGameBuilder->getDealer();

	mView = new View();
	mSequence = new Sequence( dealer, mView, this );


	mSequence->initialize( *mConfig );

	return ST_PLAY;
}

GameMain::State GameMain::play()
{
	mSequence->start();
	cleanUp();

	return getMoveTo();
}

void GameMain::cleanUp()
{
	SAFE_DELETE( mSequence );
	SAFE_DELETE( mView );
	SAFE_DELETE( mGameBuilder );
	SAFE_DELETE( mConfig );
}

GameMain::State GameMain::getMoveTo()
{
	assert( mMoveTo != ST_NONE );
	State tmp = mMoveTo;
	mMoveTo = ST_NONE;
	return tmp;
}
