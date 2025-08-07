#pragma once
#include "Constants_Game.h"

class Dealer;
class Player;
class Config;

class MatchCondition
{
public:
	MatchCondition( const Config* );
	virtual ~MatchCondition(void);

	virtual void initialize( const Config* );
	bool isMatchFinish( Dealer* );
	void addPlayer( Player* );
	int getPlayerNum() const;
	const Player& getPlayer( int ) const;
	int getRank( int ) const;

private:
	virtual bool isMatchFinishSub( Dealer* ) = 0;

	int mPlayerNum;
	Player* mPlayers[PLAYER_MAX];
	Player* mResults[PLAYER_MAX];
	int mRanks[PLAYER_MAX];
	int mRestPlayerNum;
};
