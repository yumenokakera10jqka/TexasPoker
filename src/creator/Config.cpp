#include "Config.h"
#include "Constants_View.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#define GAMETITLE "�e�L�T�X�z�[���f��"
#define MSG_URGE "���[���ɑΉ������ԍ��𔼊p�����œ��͂��Ă�������"
#define MSG_NTIMES "�����ɂ��邩�𔼊p�����œ��͂��Ă��������i�ŏ� 1�^�ő� 100�j"
#define MSG_CHIP "�����`�b�v�𔼊p�����œ��͂��Ă��������i�ŏ� 100�^�ő� 10000�j"
#define MSG_BET "�����x�b�g�z�𔼊p�����œ��͂��Ă��������i�ŏ� 10�^�ő� �����`�b�v�Ɠ��z�j"
#define NTIMES_MIN 1
#define NTIMES_MAX 100
#define CHIP_MIN 100
#define CHIP_MAX 10000
#define BET_MIN 10

#define MENUNUM 6
static string gStartMenu[] = {"�P�F�T��폟���i�����`�b�v2000�^�����a�d�s�z100�j"
, "�Q�F�m��폟���i�����ŏ����ݒ肷��j"
, "�R�F�m��폟���i�����ŉ����̂ݐݒ肷��j"
, "�S�F�T�o�C�o���i������������܂ő����i�����`�b�v1000�^�����a�d�s�z100�j"
, "�T�F�T�o�C�o���i�����ŏ����ݒ肷��j"
, "�U�F�Q�[�����I������"};

Config::Config(void): mPlayerName( "���Ȃ�" ), mPlayerNum( PLAYER_MAX ), mChip( 2000 ), mBet( 100 )
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
