#pragma once
#include "Constants_Game.h"
#include <string>

using namespace std;

class Config
{
public:

	enum GameRule
	{
		GR_NTIMES,
		GR_SURVIVAL
	};

	Config(void);
	~Config(void);

	bool startMenu();

	string getName() const;
	int getPlayerNum() const;
	int getChipAmount() const;
	int getBet() const;
	int getRoundNum() const;
	void getCardNumToTable( int* dst ) const;
	int getCardNumToPlayer() const;
	int getGameNum() const;
	GameRule getGameRule() const;

private:
	void requestNTimes();
	void request();

	string mPlayerName;
	int mPlayerNum;
	int mChip;
	int mBet;
	int mRoundNum;
	int mCardNumToTable[ROUND_MAX + 1];
	int mCardNumToPlayer;
	int mGameNum;
	GameRule mGameRule;
};
