#pragma once

class Yaku;
class Action;
class Player;

class Decision
{
public:
	Decision(void){};
	virtual ~Decision(void){};

	virtual void setPlayer( Player* ) = 0;
	virtual void decide( const Yaku&, Action* ) = 0;
	virtual void prepareRound() = 0;

};
