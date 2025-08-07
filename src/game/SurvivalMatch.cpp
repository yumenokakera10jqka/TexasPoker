#include "SurvivalMatch.h"
#include "Config.h"
#include "Dealer.h"
#include "Player.h"

SurvivalMatch::SurvivalMatch( const Config* con ): MatchCondition( con )
{
}

SurvivalMatch::~SurvivalMatch(void)
{
}

void SurvivalMatch::initialize( const Config* con )
{
	MatchCondition::initialize( con );
}

bool SurvivalMatch::isMatchFinishSub( Dealer* dealer )
{
	const Player& p = dealer->getParticipant( MANUALPLAYER_INDEX );

	if( p.getTurnState() == Player::TURN_ELIMINATED )
	{
		return true;
	}

	return false;
}

