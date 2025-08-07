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
	// �X�^�b�N�̎c���Ă���v���C���[������ԃ��[�v
	while( restPlayerNum > 0 )
	{
		// �����v���C���[���m�肷��
		int winner = FUNC_WINNERNUM( restPlayerNum );

		// �����v���C���[�̒��ōł��������X�^�b�N�`�b�v�z���擾����
		int lowest = FUNC_LOWESTSTACK( winner );

		// �e�v���C���[�̃X�^�b�N�`�b�v����lowestStack�ȉ��̃`�b�v�𒥎�����
		int mainPot = FUNC_CREATEMAINPOT( restPlayerNum, lowest );

		// ���C���|�b�g�������v���C���[�ɕ��z
		FUNC_DISTRIBUTEMAINPOT( winner, mainPot );

		// �X�^�b�N�`�b�v��0�̃v���C���[������
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
	//�[���̓|�W�V������LB�ɍł��߂��v���C���[�Ɏx����
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
