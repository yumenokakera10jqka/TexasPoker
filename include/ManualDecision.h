#pragma once
#include "decision.h"

class Yaku;
class Player;

class ManualDecision : public Decision
{
public:
	ManualDecision();
	~ManualDecision(void);

	void setPlayer( Player* );
	void decide( const Yaku&, Action* ); //TODO:UPDATE ActionMenuMediator‚©‚çinput‚ðŽæ“¾‚µ‚ÄƒAƒNƒVƒ‡ƒ“Œˆ’è
	void prepareRound();	//TODO:TEST

private:
	Player* mPlayer;
};
