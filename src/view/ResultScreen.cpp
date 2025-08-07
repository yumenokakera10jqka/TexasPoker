#include "ResultScreen.h"
#include "Screen.h"
#include "Format.h"
#include "MatchConditionMediator.h"
#include "DealerMediator.h"
#include <iostream>
#include <string>
#include <cassert>

#define ROW_RANK 0
#define ROW_NAME 1
#define ROW_CHIP 2
#define COL_TITLE 0
#define COL_FIRSTPLAYER 1
#define COL_LASTPLAYER 4
#define ROWSIZE 3
#define COLSIZE 5
#define COLWIDTH 10

#define WORD_RANK "順位"
#define WORD_NAME "名前"
#define WORD_CHIP "チップ"

using namespace std;

ResultScreen::ResultScreen(): mScreen( 0 )
{
	createScreen();
}

ResultScreen::~ResultScreen(void)
{
	delete( mScreen );
}

void ResultScreen::draw( View::ViewState seq )
{
	cout << endl;

	clear();
	update();
	mScreen->draw();
}

void ResultScreen::clear()
{
	for( int i = COL_FIRSTPLAYER; i <= COL_LASTPLAYER; i++ )
	{
		mScreen->clearCol( i );
	}
}

void ResultScreen::update()
{
	MatchConditionMediator* tm = MatchConditionMediator::instance();
	VValueSet rank = tm->getValue( MatchConditionMediator::MATCH_RANK );
	VValueSet name = tm->getValue( MatchConditionMediator::MATCH_PLAYERNAME );
	VValueSet chip = tm->getValue( MatchConditionMediator::MATCH_CHIPAMOUNT );
	int playerNum = rank.getSize();

	for( int i = 0; i < playerNum; i++ )
	{
		mScreen->update( ROW_RANK, COL_FIRSTPLAYER + i, rank.getVValue( i ) );
		mScreen->update( ROW_NAME, COL_FIRSTPLAYER + i, name.getVValue( i ) );
		mScreen->update( ROW_CHIP, COL_FIRSTPLAYER + i, chip.getVValue( i ) );
	}
}

void ResultScreen::update( View::ViewState seq )
{
}

void ResultScreen::createScreen()
{
	int row = ROWSIZE;
	int col = COLSIZE;
	mScreen = new Screen( row, col );

	for( int i = 0; i < row; i++ )
	{
		for( int j = 0; j < col; j++ )
		{
			Format* f = mScreen->getFormat( i, j );
			f->mWidth = COLWIDTH;
		}
	}

	mScreen->update( ROW_RANK, COL_TITLE, WORD_RANK );
	mScreen->update( ROW_NAME, COL_TITLE, WORD_NAME );
	mScreen->update( ROW_CHIP, COL_TITLE, WORD_CHIP );
}
