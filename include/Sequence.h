#pragma once
#include "Constants_Game.h"

class Dealer;
class View;
class GameMain;
class Config;

class Sequence
{
public:
	enum State
	{
		ST_PREPAREGAME,
		ST_PREPAREROUND,
		ST_CARDTOPLAYER,
		ST_CARDTOTABLE,
		ST_LITTLEBLIND,
		ST_BIGBLIND,
		ST_ROTATE,
		ST_PLAYERINPUT,
		ST_DECISION,
		ST_SHOWDOWN,
		ST_FINISHGAME,
		ST_MENU,
		ST_CLEANUP,
		ST_MATCHCONDITION,
		ST_ELIMINATE,
		ST_SIZE
	};

	Sequence( Dealer*, View*, GameMain* );
	~Sequence(void);

	void initialize( const Config& );
	void start();

private:
	State prepareGame();
	State prepareRound();
	State cardToPlayer();
	State cardToTable();
	State littleBlind();
	State bigBlind();
	State rotate();
	State playerInput();
	State decision();
	State showDown();
	State finishGame();
	State menu();
	State matchCondition();
	State eliminatePlayer();
	void cleanUp();

	Dealer* mDealer;
	View* mView;
	GameMain* mGameMain;

	State mState;
};
