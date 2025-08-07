#pragma once
#include "decision.h"
#include "Yaku.h"

class Dealer;

class AutoDecision : public Decision
{
public:
	friend class AutoDecisionTest;

	AutoDecision( Dealer* );
	~AutoDecision(void);

	void setPlayer( Player* );
	void decide( const Yaku&, Action* );
	void prepareRound();	//TODO:TEST

private:
	int calcYakuScore();
	int calcMoneyScore();
	void finalDecide( int, Action* );
	Yaku::YakuSet highCardSocre( int* );
	Yaku::YakuSet onePairScore( int* );
	Yaku::YakuSet twoPairScore( int* );
	Yaku::YakuSet threeCardScore( int* );
	Yaku::YakuSet fullHouseScore( int* );
	Yaku::YakuSet foreCardScore( int* );
	Yaku::YakuSet straightScore( int* );
	Yaku::YakuSet flushScore( int* );
	Yaku::YakuSet sFlushScore( int* );
	Yaku::YakuSet royalScore( int* );

	Dealer* mDealer;
	Player* mPlayer;
	Yaku mYaku;
	int mScore;
	int mRaiseNum;
};
