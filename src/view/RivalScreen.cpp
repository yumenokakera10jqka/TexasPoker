#include "RivalScreen.h"
#include "Constants_View.h"
#include "FlexScreen.h"
#include "Format.h"
#include "Document.h"
#include "Element.h"
#include "Attribute.h"
#include "Loader.h"
#include "File.h"
#include <iostream>
#include <string>
#include <cassert>

#define COL_TITLE_NAME "titleName"
#define COL_TITLE_CHIP "titleChip"
#define COL_TITLE_BET "titleBet"
#define COL_TITLE_HAND "titleHand"
#define COL_TITLE_ACTION "titleAction"
#define COL_TITLE_STATE "titleState"
#define COL_TITLE_NAME_WORD "対戦相手名"
#define COL_TITLE_CHIP_WORD "所持チップ"
#define COL_TITLE_BET_WORD "賭けチップ"
#define COL_TITLE_HAND_WORD "ハンドカード"
#define COL_TITLE_ACTION_WORD "アクション"
#define COL_TITLE_STATE_WORD ""

static string gColName[] = { "cpu1Name", "cpu2Name", "cpu3Name" };
static string gColChip[] = { "cpu1Chip", "cpu2Chip", "cpu3Chip" };
static string gColBet[] = { "cpu1Bet", "cpu2Bet", "cpu3Bet" };
static string gColHand[] = { "cpu1Hand1", "cpu1Hand2", "cpu2Hand1", "cpu2Hand2", "cpu3Hand1", "cpu3Hand2" };
static string gColAction[] = { "cpu1Action", "cpu2Action", "cpu3Action" };
static string gColState[] = { "cpu1State", "cpu2State", "cpu3State" };

using namespace std;

RivalScreen::RivalScreen(): mScreen( 0 )
{
	createScreen();
}

RivalScreen::~RivalScreen(void)
{
	delete( mScreen );
}

void RivalScreen::draw( View::ViewState seq )
{
	cout << endl;
	clear();

	update( seq );
	drawHeader();
	mScreen->draw();
}

void RivalScreen::clear()
{
	mScreen->clear();
}

void RivalScreen::update( View::ViewState seq )
{
	PlayerMediator* pm = PlayerMediator::instance();
	pm->selectPlayer( PlayerMediator::PLAYER_CPU );

	int idx = 0;
	while( true )
	{
		mScreen->update( gColName[idx], pm->getValue( PlayerMediator::PLAYER_NAME ).getVValue() );
		mScreen->update( gColChip[idx], pm->getValue( PlayerMediator::PLAYER_CHIP ).getVValue() );
		mScreen->update( gColBet[idx], pm->getValue( PlayerMediator::PLAYER_STACKCHIP ).getVValue() );
		VValueSet atSet = pm->getValue( PlayerMediator::PLAYER_HAND );
		int cardNum = atSet.getSize();
		for( int i = 0; i < cardNum; i++ )
		{
			mScreen->update( gColHand[(idx*2)+i], atSet.getVValue( i ) );

		}

		switch( seq )
		{
		case View::VST_FINISHGAME:
			mScreen->update( gColAction[idx], pm->getValue( PlayerMediator::PLAYER_YAKU ).getVValue()
							, Format::COLOR_RED );
			mScreen->update( gColState[idx], pm->getValue( PlayerMediator::PLAYER_WIN ).getVValue()
							, Format::COLOR_RED );
			break;
		default:
			mScreen->update( gColAction[idx], pm->getValue( PlayerMediator::PLAYER_ACTION ).getVValue() );
			mScreen->update( gColState[idx], pm->getValue( PlayerMediator::PLAYER_ACTIVE ).getVValue() );
			break;
		}

		if( !( pm->next() ) )
		{
			break;
		}
		idx++;
	}

}

void RivalScreen::drawHeader()
{
	mScreen->update( COL_TITLE_NAME, COL_TITLE_NAME_WORD );
	mScreen->update( COL_TITLE_CHIP, COL_TITLE_CHIP_WORD );
	mScreen->update( COL_TITLE_BET, COL_TITLE_BET_WORD );
	mScreen->update( COL_TITLE_HAND, COL_TITLE_HAND_WORD );
	mScreen->update( COL_TITLE_ACTION, COL_TITLE_ACTION_WORD );
}

void RivalScreen::createScreen()
{
	Loader::create();
	File** tagFile = new File*();
	string path = BASEPATH;
	path += "RivalScreen.txt";
	Loader::instance()->createFile( tagFile, path.c_str() );
	Loader::instance()->update();

	Document d( (*tagFile)->getFileData() );
	Loader::instance()->destroyFile( tagFile );
	Loader::destroy();
	const Element* elements = d.getRoot()->getChilds();

	mScreen = new FlexScreen( &elements[0] );
}
