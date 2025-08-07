#include "Sequence.h"
#include "Dealer.h"
#include "View.h"
#include "GameMain.h"
#include "SelectMenu.h"
#include "Config.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

#define SEQUENCE_MENU_SIZE 3
static string gMenuWords[] = { "もう１度同じ設定でプレイする"
							, "スタートメニューに戻る"
							, "ゲームを終了する" };

Sequence::Sequence( Dealer* dealer, View* view, GameMain* gameMain ):mDealer( dealer )
					, mView( view ), mGameMain( gameMain ), mState( Sequence::ST_PREPAREGAME )
{
}

Sequence::~Sequence(void)
{
}

void Sequence::initialize( const Config& con )
{
}

void Sequence::start()
{
	bool continueGame = true;
	State newState = mState;

	while( continueGame )
	{
		switch( mState )
		{
		case ST_MATCHCONDITION:
			newState = matchCondition();
			break;
		case ST_PREPAREGAME:
			newState = prepareGame();
			break;
		case ST_PREPAREROUND:
			newState = prepareRound();
			break;
		case ST_LITTLEBLIND:
			newState = littleBlind();
			break;
		case ST_BIGBLIND:
			newState = bigBlind();
			break;
		case ST_CARDTOPLAYER:
			newState = cardToPlayer();
			break;
		case ST_CARDTOTABLE:
			newState = cardToTable();
			break;
		case ST_ROTATE:
			newState = rotate();
			break;
		case ST_PLAYERINPUT:
			newState = playerInput();
			break;
		case ST_DECISION:
			newState = decision();
			break;
		case ST_SHOWDOWN:
			newState = showDown();
			break;
		case ST_FINISHGAME:
			newState = finishGame();
			break;
		case ST_ELIMINATE:
			newState = eliminatePlayer();
			break;
		case ST_MENU:
			newState = menu();
			break;
		case ST_CLEANUP:
			cleanUp();
			continueGame = false;
			break;
		default:
			assert( false );
		}
				
		mState = newState;
	}
}

Sequence::State Sequence::prepareGame()
{
	mDealer->prepareGame();
	mView->drawGameStart();
	return Sequence::ST_PREPAREROUND;
}

Sequence::State Sequence::prepareRound()
{
	mDealer->prepareRound();
	mView->drawRoundStart();

	if( mDealer->getRound() == 1 )
	{
		return ST_LITTLEBLIND;
	}
	return ST_CARDTOTABLE;
}

Sequence::State Sequence::cardToPlayer()
{
	mDealer->cardToPlayer();
	mView->draw( View::VST_CARDTOPLAYER );
	return ST_ROTATE;
}

Sequence::State Sequence::cardToTable()
{
	mDealer->cardToTable();
	mView->draw( View::VST_CARDTOTABLE );
	return ST_ROTATE;
}

Sequence::State Sequence::littleBlind()
{
	mDealer->littleBlind();
	return ST_BIGBLIND;
}

Sequence::State Sequence::bigBlind()
{
	mDealer->bigBlind();
	return ST_CARDTOPLAYER;
}

Sequence::State Sequence::rotate()
{
	bool isContinue = mDealer->rotate();

	// ラウンド続行の場合
	if( isContinue )
	{
		if( mDealer->isManualPlayer() )
		{
			return ST_PLAYERINPUT;
		}
		return ST_DECISION;
	}
	// ゲーム終了の場合
	if( mDealer->isGameFinished() )
	{
		return ST_FINISHGAME;
	}
	// 既定数のラウンド終了の場合
	if( mDealer->isRoundComplete() )
	{
		return ST_SHOWDOWN;
	}
	return ST_PREPAREROUND;
}

Sequence::State Sequence::playerInput()
{
	mView->draw( View::VST_PLAYERINPUT );
	return ST_DECISION;
}

Sequence::State Sequence::decision()
{
	mDealer->updateCurrentPlayer();
	if( !( mDealer->isManualPlayer() ) )
	{
		mView->draw( View::VST_CPUDECISION );
	}
	return ST_ROTATE;
}

Sequence::State Sequence::showDown()
{
	mDealer->showDown();
	mView->draw( View::VST_SHOWDOWN );
	return ST_FINISHGAME;
}

Sequence::State Sequence::finishGame()
{
	mDealer->finishGame();
	mView->draw( View::VST_FINISHGAME );
	return ST_ELIMINATE;
}

Sequence::State Sequence::menu()
{
	SelectMenu sm( SEQUENCE_MENU_SIZE );
	for( int i = 0; i < SEQUENCE_MENU_SIZE; i++ )
	{
		sm.addWord( gMenuWords[i] );
	}
	sm.draw();
	int res = sm.getInput();

	switch( res )
	{
	case 0:
		mGameMain->gameInitialize();
		return ST_PREPAREGAME;
	case 1:
		mGameMain->moveTo( GameMain::ST_STARTMENU );
		return ST_CLEANUP;
	case 2:
		mGameMain->moveTo( GameMain::ST_EXIT );
		return ST_CLEANUP;
	default:
		mGameMain->moveTo( GameMain::ST_EXIT );
		return ST_CLEANUP;
	}
}

void Sequence::cleanUp()
{
}

Sequence::State Sequence::matchCondition()
{
	if( mDealer->isMatchFinish() )
	{
		mView->drawResult();
		return ST_MENU;
	}
	return ST_PREPAREGAME;
}

Sequence::State Sequence::eliminatePlayer()
{
	mDealer->eliminatePlayer();
	return ST_MATCHCONDITION;
}
