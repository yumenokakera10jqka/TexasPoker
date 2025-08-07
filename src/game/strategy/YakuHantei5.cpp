#include "YakuHantei5.h"
#include "Card.h"
#include <cassert>

#define YAKUHANTEI_NOTEXIST -1

#ifndef TEST_YAKUHANTEI5

	#define FUNC_RESET reset
	#define FUNC_ANALIZE analyze
	#define FUNC_ISROYAL isRoyalStraightFlush
	#define FUNC_ISSTRAIGHTFLUSH isStraightFlush
	#define FUNC_ISFLUSH isFlush
	#define FUNC_ISSTRAIGHT isStraight
	#define FUNC_ISFORECARD isForeCard
	#define FUNC_ISFULLHOUSE isFullHouse
	#define FUNC_ISTHREECARD isThreeCard
	#define FUNC_ISTWOPAIR isTwoPair
	#define FUNC_ISONEPAIR isOnePair
	#define FUNC_SETHIGHCARD setHighCard

#endif

using namespace std;

YakuHantei5::YakuHantei5(void): mCards( YAKUCARD_NUM ), mIsSet( false ), mForePairNum( YAKUHANTEI_NOTEXIST )
							, mThreePairNum( YAKUHANTEI_NOTEXIST ), mPairCount( 0 )
							, mIsRoyal( false ), mIsRenban( false ), mIsSingleSuit( false )
{
	for( int i = 0; i < YAKUHANTEI5_PAIRCOUNT_MAX; i++ )
	{
		mPairNum[i] = YAKUHANTEI_NOTEXIST;
	}
}

YakuHantei5::~YakuHantei5(void)
{
}

int YakuHantei5::numInCharge() const
{
	return YAKUCARD_NUM;
}

void YakuHantei5::setCards( Card** srcCards )
{
	assert( srcCards != 0 );

	FUNC_RESET();

	for( int i = 0; i < YAKUCARD_NUM; i++ )
	{
		assert( srcCards[i] != 0 );

		mCards.add( srcCards[i] );
	}

	mIsSet = true;

	FUNC_ANALIZE();
}

bool YakuHantei5::hantei()
{
	if( !mIsSet ){ return false; }

	// is～関数は判定が独立しているので順番を変えても結果は変わらない
	if( FUNC_ISONEPAIR() )
	{
		return true;
	}
	if( FUNC_ISTWOPAIR() )
	{
		return true;
	}
	if( FUNC_ISTHREECARD() )
	{
		return true;
	}
	if( FUNC_ISSTRAIGHT() )
	{
		return true;
	}
	if( FUNC_ISFLUSH() )
	{
		return true;
	}
	if( FUNC_ISFULLHOUSE() )
	{
		return true;
	}
	if( FUNC_ISFORECARD() )
	{
		return true;
	}
	if( FUNC_ISSTRAIGHTFLUSH() )
	{
		return true;
	}
	if( FUNC_ISROYAL() )
	{
		return true;
	}

	// 役無しの場合はハイカードをセットする
	// 必ず全ての役判定が終了した後に呼び出す
	FUNC_SETHIGHCARD();

	return false;
}

bool YakuHantei5::hanteiRiichi()
{
	return false;
}

const Yaku& YakuHantei5::getYaku() const
{
	return mYaku;
}

bool YakuHantei5::isRoyalStraightFlush()
{
	if( mIsRoyal )
	{
		setYakuAllCard( Yaku::YAKU_ROYALSTRAIGHTFLUSH );
		return true;
	}

	return false;
}

bool YakuHantei5::isStraightFlush()
{
	if( mIsRenban && mIsSingleSuit )
	{
		setYakuAllCard( Yaku::YAKU_STRAIGHTFLUSH );
		return true;
	}

	return false;
}

bool YakuHantei5::isFlush()
{
	if( mIsSingleSuit && !mIsRenban && !mIsRoyal )
	{
		setYakuAllCard( Yaku::YAKU_FLUSH );
		return true;
	}

	return false;
}

bool YakuHantei5::isStraight()
{
	if( mIsRenban && !mIsSingleSuit )
	{
		setYakuAllCard( Yaku::YAKU_STRAIGHT );
		return true;
	}
	return false;
}

bool YakuHantei5::isForeCard()
{
	if( mForePairNum != YAKUHANTEI_NOTEXIST )
	{
		setYakuPairCard( Yaku::YAKU_FORECARD, mForePairNum, YAKUHANTEI_NOTEXIST );
		return true;
	}

	return false;
}

bool YakuHantei5::isFullHouse()
{
	if( mThreePairNum != YAKUHANTEI_NOTEXIST && mPairCount == 1 )
	{
		setYakuPairCard( Yaku::YAKU_FULLHOUSE, mThreePairNum, mPairNum[0] );
		return true;
	}

	return false;
}

bool YakuHantei5::isThreeCard()
{
	if( mThreePairNum != YAKUHANTEI_NOTEXIST && mPairCount == 0 )
	{
		setYakuPairCard( Yaku::YAKU_THREECARD, mThreePairNum, YAKUHANTEI_NOTEXIST );
		return true;
	}

	return false;
}

bool YakuHantei5::isTwoPair()
{
	if( mPairCount == 2 )
	{
		setYakuPairCard( Yaku::YAKU_TWOPAIR, mPairNum[0], mPairNum[1] );
		return true;
	}

	return false;
}

bool YakuHantei5::isOnePair()
{
	if(  mPairCount == 1 && mThreePairNum == YAKUHANTEI_NOTEXIST )
	{
		setYakuPairCard( Yaku::YAKU_ONEPAIR, mPairNum[0], YAKUHANTEI_NOTEXIST );
		return true;
	}

	return false;
}

bool YakuHantei5::setHighCard()
{
	mYaku.setYaku( Yaku::YAKU_HIGHCARD );
	for( int i = 0; i < YAKUCARD_NUM; i++ )
	{
		mYaku.addNotYakuCard( mCards[i] );
	}

	return true;
}

bool YakuHantei5::isRoyalStraightFlushRiichi()
{
	return false;
}

bool YakuHantei5::isFlushRiichi()
{
	return false;
}

bool YakuHantei5::isStraightRiichi()
{
	return false;
}

void YakuHantei5::analyze()
{
	int cardNumCount[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for( int i = 0; i < YAKUCARD_NUM; i++ )
	{
		cardNumCount[mCards[i]->getNumber()]++;
	}

	// 数字の強い順にペアの有無を調べる
	// ツーペアのときに強い順にセットするため
	for( int i = CARD_HIGHNUMBER; i >= CARD_LOWNUMBER; i-- )
	{
		if( cardNumCount[i] == 4 )
		{
			mForePairNum = i;
			break;
		}
		else if( cardNumCount[i] == 3 )
		{
			mThreePairNum = i;
		}
		else if( cardNumCount[i] == 2 )
		{
			mPairNum[mPairCount++] = i;
		}
	}

	// ペアが1組でもあった場合、ストレートやフラッシュの可能性なし
	if( mForePairNum != YAKUHANTEI_NOTEXIST || mThreePairNum != YAKUHANTEI_NOTEXIST
		|| mPairCount != 0 )
	{
		return;
	}

	// 連番（A→13の繋がり無し）か、単一のスートかを調べる
	int expectNum = mCards[0]->getNumber() - 1;
	if( expectNum == 13 )
	{
		expectNum = 5;
	}
	Card::Suit expectSuit = mCards[0]->getSuit();
	bool isRenban = true;
	bool isSingleSuit = true;

	for( int i = 1; i < YAKUCARD_NUM; i++ )
	{
		if( mCards[i]->getNumber() != expectNum )
		{
			isRenban = false;
		}
		if( mCards[i]->getSuit() != expectSuit )
		{
			isSingleSuit = false;
		}
		expectNum--;
	}
	mIsRenban = isRenban;
	mIsSingleSuit = isSingleSuit;

	// ロイヤルストレートフラッシュか調べる
	// フラッシュと区別がつかないため（どちらも非連番かつ単一スート）
	if( mIsSingleSuit && !mIsRenban && mCards[0]->getNumber() == CARD_HIGHNUMBER )
	{
		bool isRoyal = true;
		int expectNum = CARD_HIGHNUMBER - 1;

		for( int i = 1; i < YAKUCARD_NUM; i++ )
		{
			if( mCards[i]->getNumber() != expectNum )
			{
				isRoyal = false;
				break;
			}
			expectNum--;
		}
		mIsRoyal = isRoyal;
	}
}

void YakuHantei5::reset()
{
	mIsSet = false;
	mForePairNum =YAKUHANTEI_NOTEXIST;
	mThreePairNum = YAKUHANTEI_NOTEXIST;
	mPairCount = 0;
	mIsRoyal = false;
	mIsRenban = false;
	mIsSingleSuit = false;

	mCards.reset();
	for( int i = 0; i < YAKUHANTEI5_PAIRCOUNT_MAX; i++ )
	{
		mPairNum[i] = YAKUHANTEI_NOTEXIST;
	}

	mYaku.reset();
}

void YakuHantei5::setYakuAllCard( Yaku::YakuSet yaku )
{
	mYaku.setYaku( yaku );
	for( int i = 0; i < YAKUCARD_NUM; i++ )
	{
		mYaku.addYakuCard( mCards[i] );
	}
}

void YakuHantei5::setYakuPairCard( Yaku::YakuSet yaku, int yakuNum1, int yakuNum2 )
{
	mYaku.setYaku( yaku );
	for( int i = 0; i < YAKUCARD_NUM; i++ )
	{
		if( mCards[i]->getNumber() == yakuNum1
			|| mCards[i]->getNumber() == yakuNum2 )
		{
			mYaku.addYakuCard( mCards[i] );
		}
		else
		{
			mYaku.addNotYakuCard( mCards[i] );
		}
	}
}