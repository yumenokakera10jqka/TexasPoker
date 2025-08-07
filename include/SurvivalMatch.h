#pragma once
#include "matchcondition.h"

class Dealer;
class Config;

class SurvivalMatch :
	public MatchCondition
{
public:
	SurvivalMatch( const Config* );
	~SurvivalMatch(void);

	void initialize( const Config* con );

private:
	bool isMatchFinishSub( Dealer* );

};
