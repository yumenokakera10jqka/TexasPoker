#include "CardPack.h"
#include "TableCard.h"
#include "Card.h"
#include "YakuHantei.h"
#include <cassert>

using namespace std;

CardPack::CardPack( TableCard* tc ): mTable( tc ), mHandNum( 0 )
{
}

CardPack::~CardPack(void)
{
	//TODO:TEST
	/*
	map<int, YakuHantei*>::iterator it;
	for( it = mYakuHantei.begin() ; it != mYakuHantei.end(); it++ ){
		delete( (*it).second );
		(*it).second = 0;
	}
	*/
}

void CardPack::addYakuHantei( YakuHantei* yakuHantei )
{
	// 担当カード枚数を聞いてキーとする
	mYakuHantei[yakuHantei->numInCharge()] = yakuHantei;
}

void CardPack::setHand( Card* card )
{
	assert( 0 <= mHandNum && mHandNum < HANDCARD_MAX );

	card->setPlace( Card::PLACE_HAND );	//TODO:テスト
	mHands[mHandNum++] = card;
}

const Card& CardPack::getHand( int pos ) const
{
	assert( 0 <= pos && pos < mHandNum );

	return *mHands[pos];
}

int CardPack::getHandNum() const
{
	return mHandNum;
}

int CardPack::getTableCardNum() const
{
	return mTable->getCardNum();
}

const Yaku& CardPack::getYaku() const
{
	return mYaku;
}

CardSetIterator CardPack::createIterator()
{
	assert( mHandNum == HANDCARD_MAX && mTable->getCardNum() >= TABLECARD_MINNUM );

	CardSetIterator cIterator( YAKUCARD_NUM );

	// イテレータに現在の全てのハンドカードをセット
	for( int i = 0; i < HANDCARD_MAX; i++ )
	{
		cIterator.setCard( mHands[i] );
	}

	Card* tableCards[TABLECARD_MAX];
	int tableCardNum = mTable->getCardNum();
	mTable->getCards( tableCards, tableCardNum );

	// イテレータに現在の全てのテーブルカードをセット
	for( int i = 0; i < tableCardNum; i++ )
	{
		cIterator.setCard( tableCards[i] );
	}

	return cIterator;
}

void CardPack::updateYaku()
{
	// ハンドカードがセットされていない場合
	if( mHandNum < HANDCARD_MAX )
	{
		return;
	}

	YakuHantei* yakuHantei = 0;

	// ハンドカードがセットされているがテーブルカードがセットされていない場合
	if( mHandNum == HANDCARD_MAX 
		&& mTable->getCardNum() < TABLECARD_MINNUM )
	{
		// 役判定オブジェクトの取得
		assert( mYakuHantei.count( mHandNum ) );
		yakuHantei = mYakuHantei[mHandNum];
		// ハンドカードのみで役更新をする
		yakuHantei->setCards( mHands );
		yakuHantei->hantei();
		mYaku = yakuHantei->getYaku();

		return;
	}

	// ハンドカードとテーブルカードが合計５枚以上ある場合
	CardSetIterator cIterator = createIterator();
	int cardNum = cIterator.getCardNum();	// ハンドとテーブルの合計カード枚数
	int selectNum = cIterator.getSelectNum();	// 判定対象のカード枚数
	Card** cardPtrs = 0;
	Yaku yakuTmp;	// 判定結果を一時的に格納
	Yaku yakuStrongest;
	yakuStrongest = mYaku;	// 最も強い役を格納
	// 役判定オブジェクトの取得
	assert( mYakuHantei.count( selectNum ) );
	yakuHantei = mYakuHantei[selectNum];

	while( ( cardPtrs = cIterator.getNextSet() ) != 0 )
	{
		yakuHantei->setCards( cardPtrs );
		yakuHantei->hantei();
		yakuTmp = yakuHantei->getYaku();
		for( int i = selectNum; i < cardNum; i++ )
		{
			yakuTmp.addNotYakuCard( cardPtrs[i] );
		}
		if( yakuTmp > yakuStrongest )
		{
			yakuStrongest = yakuTmp;
		}
	}

	if( yakuStrongest > mYaku )
	{
		mYaku = yakuStrongest;
	}
}

void CardPack::reset()
{
	for( int i = 0; i < HANDCARD_MAX; i++)
	{
		mHands[i] = 0;
	}
	mHandNum = 0;
}

void CardPack::openHand()
{
	for( int i = 0; i < mHandNum; i++)
	{
		mHands[i]->open();
	}
}

void CardPack::winGame()
{
	mYaku.winGame();
}
