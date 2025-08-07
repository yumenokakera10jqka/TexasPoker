#include "DealerMediator.h"
#include "Dealer.h"
#include "VValue.h"
#include "WordConverter.h"
#include <string>

DealerMediator* DealerMediator::mInstance = 0;

using namespace std;

DealerMediator::DealerMediator(void): mDealer( 0 )
{
}

DealerMediator::~DealerMediator(void)
{
}

void DealerMediator::create()
{
	if( mInstance ) return;

	mInstance = new DealerMediator();
} 

void DealerMediator::destroy()
{
	if( mInstance ) delete( mInstance );
	mInstance = 0;
}

DealerMediator* DealerMediator::instance()
{
	return mInstance;
}

void DealerMediator::addRefObject( Dealer* ref )
{
	mDealer = ref;
}

VValueSet DealerMediator::getValue( DealerValue dValue ) const
{
	VValueSet atSet;
	VValue at;

	switch( dValue )
	{
	case DEALER_ROUND:
		at.setValue( WordConverter::toString( mDealer->getRound() ) );
		atSet.addVValue( at );
		break;
	case DEALER_POT:
		at.setValue( WordConverter::toString( mDealer->getPot() ) );
		atSet.addVValue( at );
		break;
	case DEALER_GAME:
		at.setValue(  WordConverter::toString( mDealer->getGameNum() ) );
		atSet.addVValue( at );
		break;
	}

	return atSet;
}

