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
	void decide( const Yaku&, Action* ); //TODO:UPDATE ActionMenuMediator����input���擾���ăA�N�V��������
	void prepareRound();	//TODO:TEST

private:
	Player* mPlayer;
};
