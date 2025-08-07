#pragma once
#include "matchcondition.h"

class NTimesMatch :
	public MatchCondition
{
public:
	NTimesMatch( const Config* );
	~NTimesMatch(void);

	void initialize( const Config* con );
	int getGameNum() const;

private:
	bool isMatchFinishSub( Dealer* );
	int mGameNum;
};
