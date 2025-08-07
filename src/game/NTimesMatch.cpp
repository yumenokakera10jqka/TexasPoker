#include "NTimesMatch.h"
#include "Config.h"
#include "Dealer.h"

NTimesMatch::NTimesMatch( const Config* con ): MatchCondition( con ), mGameNum( 0 )
{
	mGameNum = con->getGameNum();
}

NTimesMatch::~NTimesMatch(void)
{
}

void NTimesMatch::initialize( const Config* con )
{
	MatchCondition::initialize( con );
}

bool NTimesMatch::isMatchFinishSub( Dealer* dealer )
{
	if( dealer->getGameNum() >= mGameNum )
	{
		return true;
	}

	return false;
}

int NTimesMatch::getGameNum() const
{
	return mGameNum;
}
