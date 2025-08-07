#include "AutoDecision.h"
#include "Dealer.h"
#include "Player.h"
#include "Card.h"
#include "Action.h"
#include "MyRandom.h"
#include <cassert>

using namespace std;

#ifndef TEST_AUTODECISION

	#define FUNC_HIGHCARDSOCRE highCardSocre
	#define FUNC_ONEPAIRSCORE onePairScore
	#define FUNC_TWOPAIRSCORE twoPairScore
	#define FUNC_THREECARDSCORE threeCardScore
	#define FUNC_FULLHOUSESCORE fullHouseScore
	#define FUNC_FORECARDSCORE foreCardScore
	#define FUNC_STRAIGHTSCORE straightScore
	#define FUNC_FLUSHSCORE flushScore
	#define FUNC_SFLUSHSCORE sFlushScore
	#define FUNC_ROYALSCORE royalScore

	#define FUNC_CALCYAKUSCORE calcYakuScore
	#define FUNC_CALCMONEYSCORE calcMoneyScore
	#define FUNC_FINALDECIDE finalDecide

#endif

#define RAISE_MAXNUM 3

#define SCORE_FOLD 20	// このスコア以下の場合フォールド確定
#define RANDOM_RANGE 100	// 高いほど弱気の選択肢をとりやすくなる
#define BET_BORDER_RATE 0.05	// 高いほどベットしやすくなる
#define CALL_BORDER_RATE 0.5	// 高いほどコールしやすくなる
// 役の基本スコア
static int g_baseScores[] = { 200, 300, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000 };
// カードの数字のスコア
static int g_numberScore[] = { 0, 0, -30, -25, -20, -15, -10, -5, 0, 5, 10, 15, 20, 25, 30 };
// 現在のラウンドによって付与されるスコア（HighCardのみ）
static int g_roundScore[] = { 0, 0, -50, -100, -150 };

AutoDecision::AutoDecision( Dealer* dealer ): mDealer( dealer ), mPlayer( 0 )
															, mScore( 0 ), mRaiseNum( 0 )
{
	assert( mDealer != 0 );
}

AutoDecision::~AutoDecision(void)
{
}

void AutoDecision::setPlayer( Player* player )
{
	mPlayer = player;
}

void AutoDecision::prepareRound()
{
	mRaiseNum = 0;
}

void AutoDecision::decide( const Yaku& yaku, Action* action )
{
	mYaku = yaku;
	mScore = 0;

	mScore += FUNC_CALCYAKUSCORE();
	mScore += FUNC_CALCMONEYSCORE();
	return FUNC_FINALDECIDE( mScore, action );
}

int AutoDecision::calcYakuScore()
{
	Yaku::YakuSet prev;
	Yaku::YakuSet current = mYaku.getYaku();

	int score = 0;

	while( true )
	{
		prev = current;
		switch( current )
		{
		case Yaku::YAKU_HIGHCARD:
			current = FUNC_HIGHCARDSOCRE( &score );
			break;
		case Yaku::YAKU_ONEPAIR:
			current = FUNC_ONEPAIRSCORE( &score );
			break;
		case Yaku::YAKU_TWOPAIR:
			current = FUNC_TWOPAIRSCORE( &score );
			break;
		case Yaku::YAKU_THREECARD:
			current = FUNC_THREECARDSCORE( &score );
			break;
		case Yaku::YAKU_FULLHOUSE:
			current = FUNC_FULLHOUSESCORE( &score );
			break;
		case Yaku::YAKU_FORECARD:
			current = FUNC_FORECARDSCORE( &score );
			break;
		case Yaku::YAKU_STRAIGHT:
			current = FUNC_STRAIGHTSCORE( &score );
			break;
		case Yaku::YAKU_FLUSH:
			current = FUNC_FLUSHSCORE( &score );
			break;
		case Yaku::YAKU_STRAIGHTFLUSH:
			current = FUNC_SFLUSHSCORE( &score );
			break;
		case Yaku::YAKU_ROYALSTRAIGHTFLUSH:
			current = FUNC_ROYALSCORE( &score );
			break;
		default:
			break;
		};
		if( current == prev )
		{
			break;
		}
	}

	return score;
}

Yaku::YakuSet AutoDecision::highCardSocre( int* dstScore )
{
	int score = 0;
	score = g_baseScores[Yaku::YAKU_HIGHCARD];
	score += g_roundScore[mDealer->getRound()];
	score += g_numberScore[mYaku.strongestCardNum( false, true )];

	*dstScore = score;
	return Yaku::YAKU_HIGHCARD;
}

Yaku::YakuSet AutoDecision::onePairScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_ONEPAIR];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;

	return Yaku::YAKU_ONEPAIR;
}
Yaku::YakuSet AutoDecision::twoPairScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}
	else if( mYaku.handNumInYaku() == 1 )
	{
		return Yaku::YAKU_ONEPAIR;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_TWOPAIR];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_TWOPAIR;
}
Yaku::YakuSet AutoDecision::threeCardScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_THREECARD];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_THREECARD;
}

Yaku::YakuSet AutoDecision::fullHouseScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_FULLHOUSE];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_FULLHOUSE;
}

Yaku::YakuSet AutoDecision::foreCardScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_FORECARD];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_FORECARD;
}
Yaku::YakuSet AutoDecision::straightScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_STRAIGHT];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_STRAIGHT;
}
Yaku::YakuSet AutoDecision::flushScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_FLUSH];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_FLUSH;
}
Yaku::YakuSet AutoDecision::sFlushScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_STRAIGHTFLUSH];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_STRAIGHTFLUSH;
}
Yaku::YakuSet AutoDecision::royalScore( int* dstScore )
{
	if( mYaku.handNumInYaku() == 0 )
	{
		return Yaku::YAKU_HIGHCARD;
	}

	int score = 0;
	score = g_baseScores[Yaku::YAKU_ROYALSTRAIGHTFLUSH];
	score += g_numberScore[mYaku.strongestCardNum( true, true )];

	*dstScore = score;
	return Yaku::YAKU_ROYALSTRAIGHTFLUSH;
}


int AutoDecision::calcMoneyScore()
{
	return 0;
}

void AutoDecision::finalDecide( int score, Action* action )
{
	if( score <= SCORE_FOLD )
	{
		return action->action( Action::CHOICE_FOLD, mPlayer );
	}

	int rndNum = MyRandom::getRandom() % RANDOM_RANGE;
	int betBorder = (int)( score * BET_BORDER_RATE );
	int callBorder = (int)( score * CALL_BORDER_RATE );

	//いけるとき
	if( rndNum < betBorder )
	{
		if( action->isPossible( Action::CHOICE_BET ) )
		{
				mRaiseNum++;	//TODO:TEST
				return action->action( Action::CHOICE_BET, mPlayer );
		}
		if( action->isPossible( Action::CHOICE_RAISE )
			&& mRaiseNum < RAISE_MAXNUM )
		{
			mRaiseNum++;	//TODO:TEST
			return action->action( Action::CHOICE_RAISE, mPlayer );
		}
		if( action->isPossible( Action::CHOICE_ALLIN ) )
		{
			return action->action( Action::CHOICE_ALLIN, mPlayer );
		}
	}
	//まあまあのとき
	if( rndNum < callBorder )
	{
		if( action->isPossible( Action::CHOICE_CALL ) )
		{
			return action->action( Action::CHOICE_CALL, mPlayer );
		}
	}
	if( action->isPossible( Action::CHOICE_CHECK ) )
	{
		return action->action( Action::CHOICE_CHECK, mPlayer );
	}
	
	action->action( Action::CHOICE_FOLD, mPlayer );
}
