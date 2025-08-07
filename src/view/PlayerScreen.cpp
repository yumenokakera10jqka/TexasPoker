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

#define INPUT_REQUIRE "�I������A�N�V�����ɑΉ������ԍ��𔼊p�����œ��͂��Ă�������"
#define INPUT_ERROR "���͂��s���ł��B������x���͂��Ă�������"
#define INPUT_OK " ��I�����܂���"

#define COL_TITLE_NAME "titleName"
#define COL_TITLE_CHIP "titleChip"
#define COL_TITLE_BET "titleBet"
#define COL_TITLE_HAND "titleHand"
#define COL_TITLE_ACTION "titleAction"
#define COL_TITLE_STATE "titleState"
#define COL_TITLE_NAME_WORD "���Ȃ��̖��O"
#define COL_TITLE_CHIP_WORD "�����`�b�v"
#define COL_TITLE_BET_WORD "�q���`�b�v"
#define COL_TITLE_HAND_WORD "�n���h�J�[�h"
#define COL_TITLE_ACTION_WORD "�A�N�V����"
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
