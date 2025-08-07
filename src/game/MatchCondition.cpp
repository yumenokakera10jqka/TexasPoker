#include "MatchCondition.h"
#include "Dealer.h"
#include "Player.h"
#include "Config.h"
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

static int CompPlayer(const void* pElem1, const void* pElem2)
{
    // pElem1 はポインタ（渡した配列の要素）へのポインタ
    const Player* pmem1 = *(const Player**)pElem1;
    const Player* pmem2 = *(const Player**)pElem2;
	const Player& p1 = *pmem1;
	const Player& p2 = *pmem2;

	if( p1.getChipAmount() < p2.getChipAmount() )
	{
		return 1;
	}

    return -1;
}

MatchCondition::MatchCondition( const Config* con ): mRestPlayerNum( 0 ), mPlayerNum( 0 )
{
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mPlayers[i] = 0;
	}
}

MatchCondition::~MatchCondition(void)
{
}

void MatchCondition::initialize( const Config* con )
{
	mRestPlayerNum = mPlayerNum;
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mRanks[i] = i + 1;
	}
}

bool MatchCondition::isMatchFinish( Dealer* dealer )
{
	if( isMatchFinishSub( dealer ) )
	{
		qsort( mPlayers, mRestPlayerNum, sizeof *mPlayers, CompPlayer );

		int rank = 1;
		mRanks[0] = rank;
		for( int i = 1; i < mRestPlayerNum; i++ )
		{
			if( mPlayers[i]->getChipAmount() < mPlayers[i-1]->getChipAmount() )
			{
				rank++;
			}
			mRanks[i] = rank;
		}

		return true;
	}

	int swapPos = mRestPlayerNum - 1;
	for( int i = mRestPlayerNum - 1; i >= 0; i-- )
	{
		if( mPlayers[i]->getTurnState() == Player::TURN_ELIMINATED )
		{
			Player* tmp = mPlayers[i];
			mPlayers[i] = mPlayers[swapPos];
			mPlayers[swapPos] = tmp;
			swapPos--;
		}
	}
	int prevRest = mRestPlayerNum;
	mRestPlayerNum = swapPos + 1;

	for( int i = mRestPlayerNum; i < prevRest; i++ )
	{
		mRanks[i] = mRestPlayerNum + 1;
	}

	if( mRestPlayerNum <= 1  )
	{
		return true;
	}
	return false;
}

void MatchCondition::addPlayer( Player* player )
{
	assert( mPlayerNum < PLAYER_MAX );

	mPlayers[mPlayerNum++] = player;
}

int MatchCondition::getPlayerNum() const
{
	return mPlayerNum;
}

const Player& MatchCondition::getPlayer( int idx ) const
{
	return *(mPlayers[idx]);
}

int MatchCondition::getRank( int idx ) const
{
	return mRanks[idx];
}
