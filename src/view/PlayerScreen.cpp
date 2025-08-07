#include "PlayerScreen.h"
#include "Constants_View.h"
#include "ActionMenuMediator.h"
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

#define INPUT_REQUIRE "選択するアクションに対応した番号を半角数字で入力してください"
#define INPUT_ERROR "入力が不正です。もう一度入力してください"
#define INPUT_OK " を選択しました"

#define COL_TITLE_NAME "titleName"
#define COL_TITLE_CHIP "titleChip"
#define COL_TITLE_BET "titleBet"
#define COL_TITLE_HAND "titleHand"
#define COL_TITLE_ACTION "titleAction"
#define COL_TITLE_STATE "titleState"
#define COL_TITLE_NAME_WORD "あなたの名前"
#define COL_TITLE_CHIP_WORD "所持チップ"
#define COL_TITLE_BET_WORD "賭けチップ"
#define COL_TITLE_HAND_WORD "ハンドカード"
#define COL_TITLE_ACTION_WORD "アクション"
#define COL_TITLE_STATE_WORD ""

static string gColName[] = { "playerName" };
static string gColChip[] = { "playerChip" };
static string gColBet[] = { "playerBet" };
static string gColHand[] = { "playerHand1", "playerHand2" };
static string gColAction[] = { "playerAction" };
static string gColState[] = { "playerState" };
static string gColActionMenu[] = { "actionMenu1", "actionMenu2", "actionMenu3", "actionMenu4"
									, "actionMenu5", "actionMenu6" };

using namespace std;

PlayerScreen::PlayerScreen(): mScreen( 0 )
{
	createScreen();
}

PlayerScreen::~PlayerScreen(void)
{
	delete( mScreen );
}

void PlayerScreen::draw( View::ViewState seq )
{
	cout << endl;
	clear();

	update( seq );
	drawHeader();
	if( seq == View::VST_PLAYERINPUT )
	{
		updateActionCol();
		mScreen->draw();
		getInput();
	}
	else
	{
		mScreen->draw();
	}
}

void PlayerScreen::clear()
{
	mScreen->clear();
}

void PlayerScreen::update( View::ViewState seq )
{
	PlayerMediator* pm = PlayerMediator::instance();
	pm->selectPlayer( PlayerMediator::PLAYER_MAN );

	int idx = 0;
	mScreen->update( gColName[idx], pm->getValue( PlayerMediator::PLAYER_NAME ).getVValue() );
	mScreen->update( gColChip[idx], pm->getValue( PlayerMediator::PLAYER_CHIP ).getVValue() );
	mScreen->update( gColBet[idx], pm->getValue( PlayerMediator::PLAYER_STACKCHIP ).getVValue() );
	VValueSet atSet = pm->getValue( PlayerMediator::PLAYER_HAND );
	int cardNum = atSet.getSize();
	for( int i = 0; i < cardNum; i++ )
	{
		mScreen->update( gColHand[i], atSet.getVValue( i ) );

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
}

void PlayerScreen::updateActionCol()
{
	ActionMenuMediator* am = ActionMenuMediator::instance();

	VValueSet atSet = am->getValue( ActionMenuMediator::ACTION_MENU );

	for( int i = 0; i < atSet.getSize(); i++ )
	{
		mScreen->update( gColActionMenu[i], atSet.getVValue( i ) );
	}
}

void PlayerScreen::getInput()
{
	cout << endl;
	cout << INPUT_REQUIRE << endl;

	int input = -1;
	ActionMenuMediator* am = ActionMenuMediator::instance();

	while( true )
	{
		cin >> input;

		if( am->setInput( input ) )
		{
			cout << am->getSelectMenu() << INPUT_OK << endl;
			getchar();
			break;
		}
		cout << INPUT_ERROR << endl;
	}
}

void PlayerScreen::drawHeader()
{
	mScreen->update( COL_TITLE_NAME, COL_TITLE_NAME_WORD );
	mScreen->update( COL_TITLE_CHIP, COL_TITLE_CHIP_WORD );
	mScreen->update( COL_TITLE_BET, COL_TITLE_BET_WORD );
	mScreen->update( COL_TITLE_HAND, COL_TITLE_HAND_WORD );
	mScreen->update( COL_TITLE_ACTION, COL_TITLE_ACTION_WORD );
}

void PlayerScreen::createScreen()
{
	Loader::create();
	File** tagFile = new File*();
	string path = BASEPATH;
	path += "PlayerScreen.txt";
	Loader::instance()->createFile( tagFile, path.c_str() );
	Loader::instance()->update();

	Document d( (*tagFile)->getFileData() );
	Loader::instance()->destroyFile( tagFile );
	Loader::destroy();
	const Element* elements = d.getRoot()->getChilds();

	mScreen = new FlexScreen( &elements[0] );
}
