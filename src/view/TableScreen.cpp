#include "TableScreen.h"
#include "Constants_View.h"
#include "TableCardMediator.h"
#include "DealerMediator.h"
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
#define MES_CARDTOTABLE "新たなカードが場に置かれました"
#define MES_CARDTOPLAYER "プレイヤーにカードが配られました"
#define MES_SHOWDOWN "ＳＨＯＷ　ＤＯＷＮ"

#define COL_TITLE_POT "titlePot"
#define COL_TITLE_POT_WORD "POT"

static string gColMessage[] = { "message" };
static string gColTableCard[] = { "tableCard1", "tableCard2", "tableCard3", "tableCard4", "tableCard5" };
static string gColPot[] = { "pot" };

using namespace std;

TableScreen::TableScreen(): mScreen( 0 )
{
	createScreen();
}

TableScreen::~TableScreen(void)
{
	delete( mScreen );
}

void TableScreen::draw( View::ViewState seq )
{
	cout << endl;
	clear();

	update( seq );
	drawHeader();
	mScreen->draw();
	cout << endl;
}

void TableScreen::clear()
{
	mScreen->clear();
}

void TableScreen::update( View::ViewState seq )
{
	TableCardMediator* tcm = TableCardMediator::instance();

	VValueSet atSet = tcm->getValue( TableCardMediator::TABLECARD_CARD );
	int cardNum = atSet.getSize();
	for( int i = 0; i < cardNum; i++ )
	{
		mScreen->update( gColTableCard[i], atSet.getVValue( i ) );

	}

	// ポットを更新
	DealerMediator* dm = DealerMediator::instance();
	mScreen->update( gColPot[0], dm->getValue( DealerMediator::DEALER_POT ).getVValue() );

	switch( seq )
	{
	case View::VST_CARDTOTABLE:
		mScreen->update( gColMessage[0], MES_CARDTOTABLE, Format::COLOR_RED );
		break;
	case View::VST_CARDTOPLAYER:
		mScreen->update( gColMessage[0], MES_CARDTOPLAYER, Format::COLOR_RED );
		break;
	case View::VST_SHOWDOWN:
		mScreen->update( gColMessage[0], MES_SHOWDOWN, Format::COLOR_RED );
		break;
	default:
		break;
	}
}

void TableScreen::drawHeader()
{
	mScreen->update( COL_TITLE_POT, COL_TITLE_POT_WORD );
}

void TableScreen::createScreen()
{
	Loader::create();
	File** tagFile = new File*();
	string path = BASEPATH;
	path += "TableScreen.txt";
	Loader::instance()->createFile( tagFile, path.c_str() );
	Loader::instance()->update();

	Document d( (*tagFile)->getFileData() );
	Loader::instance()->destroyFile( tagFile );
	Loader::destroy();
	const Element* elements = d.getRoot()->getChilds();

	mScreen = new FlexScreen( &elements[0] );
}
