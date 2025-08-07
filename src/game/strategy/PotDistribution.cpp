#include "PotDistribution.h"
#include "Player.h"
#include <cassert>

#ifndef TEST_POTDISTRIBUTION
	#define FUNC_WINNERNUM winnerNum
	#define FUNC_LOWESTSTACK lowestStack
	#define FUNC_CREATEMAINPOT createMainPot
	#define FUNC_DISTRIBUTEMAINPOT distributeMainPot
	#define FUNC_SHORTESTPLAYER shortestPlayer
	#define FUNC_REMOVESTACKZEROPLAYER removeStackZeroPlayer
#endif


PotDistribution::PotDistribution(void): mPlayerNum( 0 ), mBet( 0 )
{
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mPlayers[i] = 0;
	}
}

PotDistribution::~PotDistribution(void)
{
}

void PotDistribution::initialize( Player** strongOrder, int playerNum, int bet )
{
	mBet = bet;
	mPlayerNum = playerNum;
	for( int i = 0; i < mPlayerNum; i++ )
	{
		mPlayers[i] = strongOrder[i];
	}
}

void PotDistribution::distribute()
{
	assert( mPlayerNum != 0 );

	int restPlayerNum = mPlayerNum;
	// スタックの残っているプレイヤーがいる間ループ
	while( restPlayerNum > 0 )
	{
		// 勝利プレイヤーを確定する
		int winner = FUNC_WINNERNUM( restPlayerNum );

		// 勝利プレイヤーの中で最も小さいスタックチップ額を取得する
		int lowest = FUNC_LOWESTSTACK( winner );

		// 各プレイヤーのスタックチップからlowestStack以下のチップを徴収する
		int mainPot = FUNC_CREATEMAINPOT( restPlayerNum, lowest );

		// メインポットを勝利プレイヤーに分配
		FUNC_DISTRIBUTEMAINPOT( winner, mainPot );

		// スタックチップが0のプレイヤーを除去
		restPlayerNum = FUNC_REMOVESTACKZEROPLAYER( restPlayerNum );
	}
}

int PotDistribution::winnerNum( int size ) const
{
	int winnerNum = 1;
	while( winnerNum < size )
	{
		if( !( *( mPlayers[winnerNum] ) == *( mPlayers[winnerNum - 1] ) ) )
		{
			break;
		}
		winnerNum++;
	}
	return winnerNum;
}

int PotDistribution::lowestStack( int size ) const
{
	int lowestStack = mPlayers[0]->getStackChipAmount();
	for( int i = 1; i < size; i++ )
	{
		int playerStack = mPlayers[i]->getStackChipAmount();
		if( playerStack < lowestStack )
		{
			lowestStack = playerStack;
		}
	}
	return lowestStack;
}

int PotDistribution::createMainPot( int size, int lowestStack )
{
	int mainPot = 0;
	for( int i = 0; i < size; i++ )
	{
		int pop = lowestStack;
		int playerStack = mPlayers[i]->getStackChipAmount();
		if( playerStack < lowestStack )
		{
			pop = playerStack;
		}
		mPlayers[i]->popChip( pop );
		mainPot += pop;
	}
	return mainPot;
}

void PotDistribution::distributeMainPot( int size, int mainPot )
{
	int payUnit = mBet;
	int diff = payUnit * size;
	int payDiff = mainPot / diff ;
	int pay = payDiff * payUnit;
	for( int i = 0; i < size; i++ )
	{
		mPlayers[i]->deposit( pay );
		mPlayers[i]->gainChip( pay );
	}
	//端数はポジションのLBに最も近いプレイヤーに支払い
	int fraction = mainPot % diff;
	if( fraction >0 )
	{
		int shortest = shortestPlayer( size );
		mPlayers[shortest]->deposit( fraction );
		mPlayers[shortest]->gainChip( fraction );
	}
}

int PotDistribution::shortestPlayer( int size ) const
{
	int shortest = mPlayers[0]->getPosition();
	int shortestPlayer = 0;
	for( int i = 1 ; i < size; i++ )
	{
		int distance = mPlayers[i]->getPosition();
		if( distance < shortest )
		{
			shortest = distance;
			shortestPlayer = i;
		}
	}
	return shortestPlayer;
}

int PotDistribution::removeStackZeroPlayer( int size )
{
	int restPlayerNum = 0;
	for( int i = 0; i < size; i++ )
	{
		if( mPlayers[i]->getStackChipAmount() > 0 )
		{
			mPlayers[restPlayerNum] = mPlayers[i];
			restPlayerNum++;
		}
	}
	return restPlayerNum;
}
