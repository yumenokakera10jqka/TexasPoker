#include "TableCardMediator.h"
#include "TableCard.h"
#include "WordConverter.h"
#include "Card.h"
#include "Format.h"
#include "VValue.h"
#include <string>
#include <cassert>

TableCardMediator* TableCardMediator::mInstance = 0;

using namespace std;

TableCardMediator::TableCardMediator(void): mTableCard( 0 )
{
}

TableCardMediator::~TableCardMediator(void)
{
}

void TableCardMediator::create()
{
	if( mInstance ) return;

	mInstance = new TableCardMediator();
} 

void TableCardMediator::destroy()
{
	if( mInstance ) delete( mInstance );
	mInstance = 0;
}

TableCardMediator* TableCardMediator::instance()
{
	return mInstance;
}

void TableCardMediator::addRefObject( TableCard* tc )
{
	mTableCard = tc;
}

VValueSet TableCardMediator::getValue( TableCardValue tcValue ) const
{
	VValueSet atSet;
	VValue at;

	switch( tcValue )
	{
	case TABLECARD_CARD:
		for( int i = 0; i < mTableCard->getCardNum(); i++ )
		{
			const Card& card = mTableCard->get( i );
			at.clear();
			at.setValue( WordConverter::convertCard( card ) );
			at.setColor( WordConverter::getSuitColor( card ) );
			if( mTableCard->isShowDown() && card.isWin() )
			{
				at.getFormat()->mDeco = Format::DECO_SHARP;
			}
			atSet.addVValue( at );
		}
		break;
	}

	return atSet;
}

