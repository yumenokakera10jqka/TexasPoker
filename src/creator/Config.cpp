#include "Config.h"
#include "Constants_View.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#define GAMETITLE "テキサスホールデム"
#define MSG_URGE "ルールに対応した番号を半角数字で入力してください"
#define MSG_NTIMES "何回戦にするかを半角数字で入力してください（最小 1／最大 100）"
#define MSG_CHIP "所持チップを半角数字で入力してください（最小 100／最大 10000）"
#define MSG_BET "初期ベット額を半角数字で入力してください（最小 10／最大 所持チップと同額）"
#define NTIMES_MIN 1
#define NTIMES_MAX 100
#define CHIP_MIN 100
#define CHIP_MAX 10000
#define BET_MIN 10

#define MENUNUM 6
static string gStartMenu[] = {"１：５回戦勝負（所持チップ2000／初期ＢＥＴ額100）"
, "２：Ｎ回戦勝負（自分で初期設定する）"
, "３：Ｎ回戦勝負（自分で何回戦のみ設定する）"
, "４：サバイバル（自分が負けるまで続く（所持チップ1000／初期ＢＥＴ額100）"
, "５：サバイバル（自分で初期設定する）"
, "６：ゲームを終了する"};

Config::Config(void): mPlayerName( "あなた" ), mPlayerNum( PLAYER_MAX ), mChip( 2000 ), mBet( 100 )
					, mRoundNum( ROUND_MAX ), mCardNumToPlayer( HANDCARD_MAX ), mGameNum( 5 )
					, mGameRule( GR_NTIMES )

{
	mCardNumToTable[0] = 0;
	mCardNumToTable[1] = 0;
	mCardNumToTable[2] = TABLECARD_MINNUM;
	mCardNumToTable[3] = 1;
	mCardNumToTable[4] = 1;
}

Config::~Config(void)
{
}

bool Config::startMenu()
{
	cout << GAMETITLE << endl << endl;
	cout << WORD_KEISEN << endl << endl;

	for( int i = 0; i < MENUNUM; i++ )
	{
		cout << gStartMenu[i] << endl;
	}

	cout << endl << WORD_KEISEN << endl;
	cout << MSG_URGE << endl;

	int input = -1;

	while( true )
	{
		cin >> input;

		if( 1 <= input && input <= MENUNUM )
		{
			break;
		}
		cout << MSG_URGE << endl;
	}

	input--;

	switch( input )
	{
	case 0:
		mGameRule = GR_NTIMES;
		break;
	case 1:
		mGameRule = GR_NTIMES;
		requestNTimes();
		request();
		break;
	case 2:
		mGameRule = GR_NTIMES;
		requestNTimes();
		break;
	case 3:
		mGameRule = GR_SURVIVAL;
		mChip = 1000;
		break;
	case 4:
		mGameRule = GR_SURVIVAL;
		request();
		break;
	case 5:
		return false;
	}

	return true;
}

void Config::requestNTimes()
{
	int input = -1;
	cout << MSG_NTIMES << endl;
	while( true )
	{
		cin >> input;

		if( NTIMES_MIN <= input && input <= NTIMES_MAX )
		{
			break;
		}
		cout << MSG_NTIMES << endl;
	}
	mGameNum = input;
	cout << endl << endl;
}

void Config::request()
{
	int input = -1;
	cout << MSG_CHIP << endl;
	while( true )
	{
		cin >> input;

		if( CHIP_MIN <= input && input <= CHIP_MAX )
		{
			break;
		}
		cout << MSG_CHIP << endl;
	}
	mChip = input;

	input = -1;
	cout << MSG_BET << endl;
	while( true )
	{
		cin >> input;

		if( BET_MIN <= input && input <= mChip )
		{
			break;
		}
		cout << MSG_BET << endl;
	}
	mBet = input;
	cout << endl;
}

string Config::getName() const
{
	return mPlayerName;
}

int Config::getPlayerNum() const
{
	return mPlayerNum;
}

int Config::getChipAmount() const
{
	return mChip;
}

int Config::getBet() const
{
	return mBet;
}

int Config::getRoundNum() const
{
	return mRoundNum;
}

void Config::getCardNumToTable( int* dst ) const
{
	for( int i = 0; i <= mRoundNum; i++ )
	{
		dst[i] = mCardNumToTable[i];
	}
}

int Config::getCardNumToPlayer() const
{
	return mCardNumToPlayer;
}

int Config::getGameNum() const
{
	return mGameNum;
}

Config::GameRule Config::getGameRule() const
{
	return mGameRule;
}
