#pragma once
#include "Constants_Game.h"

class TableCard;
class Dealer;
class Player;
class Config;
class YakuHantei2;
class YakuHantei5;
class MatchCondition;

class GameBuilder
{
public:
	GameBuilder( const Config* );
	~GameBuilder(void);

	Dealer* getDealer();

private:
	void build();
	void createTableCard();
	void createDealer();
	void createPlayer();

	const Config* mConfig;
	TableCard* mTableCard;
	Dealer* mDealer;
	Player* mPlayers[PLAYER_MAX];
	YakuHantei2* mYakuHantei2;
	YakuHantei5* mYakuHantei5;
	MatchCondition* mMatchCondition;	//¦Dealer‚Ådelete‚³‚ê‚é‚Ì‚Å¶¬ì‹ÆI—¹Œã‚É0‚É‚µ‚Ä‚¨‚­
};
