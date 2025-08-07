#include "MatchConditionMediator.h"
#include "MatchCondition.h"
#include "NTimesMatch.h"
#include "WordConverter.h"
#include "VValue.h"
#include "Player.h"
#include <string>

MatchConditionMediator* MatchConditionMediator::mInstance = 0;

using namespace std;

MatchConditionMediator::MatchConditionMediator(void): mMatchCondition( 0 )
{
}

MatchConditionMediator::~MatchConditionMediator(void)
{
}

void MatchConditionMediator::create()
{
	if( mInstance ) return;

	mInstance = new MatchConditionMediator();
} 

void MatchConditionMediator::destroy()
{
	if( mInstance ) delete( mInstance );
	mInstance = 0;
}

MatchConditionMediator* MatchConditionMediator::instance()
{
	return mInstance;
}

void MatchConditionMediator::addRefObject( MatchCondition* ref )
{
	mMatchCondition = ref;
}

VValueSet MatchConditionMediator::getValue( MatchConditionValue dValue ) const
{
	VValueSet atSet;
	VValue at;
	NTimesMatch* nm = 0;

	switch( dValue )
	{
	case MATCH_PLAYERNAME:
		for( int i = 0; i < mMatchCondition->getPlayerNum(); i++ )
		{
			const Player& p = mMatchCondition->getPlayer( i );
			at.setValue( p.getName() );
			atSet.addVValue( at );
		}
		break;
	case MATCH_RANK:
		for( int i = 0; i < mMatchCondition->getPlayerNum(); i++ )
		{
			at.setValue( WordConverter::toString( mMatchCondition->getRank( i ) ) );
			atSet.addVValue( at );
		}
		break;
	case MATCH_CHIPAMOUNT:
		for( int i = 0; i < mMatchCondition->getPlayerNum(); i++ )
		{
			const Player& p = mMatchCondition->getPlayer( i );
			at.setValue( WordConverter::toString( p.getChipAmount() ) );
			atSet.addVValue( at );
		}
	case MATCH_GAMENUM:
		nm = dynamic_cast<NTimesMatch*>( mMatchCondition );
		if( nm != 0 )
		{
			at.setValue( WordConverter::toString( nm->getGameNum() ) );
		}
		else
		{
			at.setValue( "Åá" );
		}
		atSet.addVValue( at );
		break;
	}

	return atSet;
}