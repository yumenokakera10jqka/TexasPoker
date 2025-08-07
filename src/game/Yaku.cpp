#include "Yaku.h"
#include <cassert>
#include <string.h>

using namespace std;

Yaku::Yaku(void): mYaku( YAKU_HIGHCARD ), mYakuCards( YAKUCARD_NUM ), mNotYakuCards( CARDSET_MAX )
{
}

/*
Yaku::Yaku( const Yaku& a )
{
	*this = a;
}
*/

Yaku::~Yaku(void)
{
}

bool Yaku::operator>( const Yaku& a ) const{    
	if ( mYaku != a.mYaku ) { return mYaku > a.mYaku; }
	// 役が同じ場合
	// 役を構成するカードの数字で判定
	for( int i = 0; i < mYakuCards.getSize(); i++ )
	{
		if( *mYakuCards[i] != *( a.mYakuCards[i] ) )
		{
			return *mYakuCards[i] > *( a.mYakuCards[i] );
		}
	}

	// 役を構成しないカードの枚数は異なる場合がある
	//※CardPack::updateで前のラウンドの役と比較する場合に発生するケース
	// カードを比較する前に枚数を確認する
	if( mNotYakuCards.getSize() != a.mNotYakuCards.getSize() )
	{
		return mNotYakuCards.getSize() > a.mNotYakuCards.getSize();
	}

	//キッカーの枚数を調べる
	//キッカーについては以下の通り
	//前提として、勝敗判定は５枚の手札を対象に行われる。ポケットであっても手札に選ばれない場合がある
	//①ポケット２枚とボード５枚全てのなかから最強の役を構成するカードが選ばれ（ワンペアなら２枚）、
	//②残り（ワンペアなら３枚）をポケットとボードの残り全てのなかから強いカードが順番に【キッカー】として選ばれる							
	int rest = YAKUCARD_NUM - mYakuCards.getSize();
	if( rest > mNotYakuCards.getSize() )
	{
		rest = mNotYakuCards.getSize();
	}

	// キッカーの数字で判定
	for( int i = 0; i < rest; i++ )
	{
		if( *mNotYakuCards[i] != *( a.mNotYakuCards[i] ) )
		{
			return *mNotYakuCards[i] > *( a.mNotYakuCards[i] );
		}
	}

	// 全く同じなら引き分け
	return false;
}

bool Yaku::operator<( const Yaku& a ) const{
	return a > *this;
}

bool Yaku::operator==( const Yaku& a ) const
{
	if( *this > a )
	{
		return false;
	}
	if( a > *this )
	{
		return false;
	}

	// 全く同じなら引き分け
	return true;
}

/*
Yaku& Yaku::operator=( const Yaku& a )
{
	mYaku = a.mYaku;
	mYakuCards = a.mYakuCards;
	mNotYakuCards = a.mNotYakuCards;

	memcpy_s( mYakuCards, sizeof( Card* ) * YAKUCARD_NUM
			, a.mYakuCards, sizeof( Card* ) * YAKUCARD_NUM );

	memcpy_s( mNotYakuCards, sizeof( Card* ) * CARDSET_MAX
		, a.mNotYakuCards, sizeof( Card* ) * CARDSET_MAX );

	return *this;
}
*/

void Yaku::setYaku( Yaku::YakuSet ys )
{
	mYaku = ys;
}

Yaku::YakuSet Yaku::getYaku() const
{
	return mYaku;
}

void Yaku::addYakuCard( Card* cd )
{
	mYakuCards.add( cd );
}

const Card* Yaku::getYakuCard( int pos ) const
{
	return mYakuCards[pos];
}

int Yaku::getYakuCardNum() const
{
	return mYakuCards.getSize();
}

void Yaku::addNotYakuCard( Card* cd )
{
	mNotYakuCards.add( cd );
}

const Card* Yaku::getNotYakuCard( int pos ) const
{
	return mNotYakuCards[pos];
}

int Yaku::getNotYakuCardNum() const
{
	return mNotYakuCards.getSize();
}

void Yaku::reset()
{
	mYaku = YAKU_HIGHCARD;
	mYakuCards.reset();
	mNotYakuCards.reset();
}

int Yaku::handNumInYaku() const
{
	int handNum = 0;

	for( int i = 0; i < mYakuCards.getSize(); i++ )
	{
		if( mYakuCards[i]->getPlace() == Card::PLACE_HAND )
		{
			handNum++;
		}
	}

	return handNum;
}

int Yaku::strongestCardNum( bool isYaku, bool isHand ) const
{
	int strongest = 0;
	Card::Place place = ( isHand )? Card::PLACE_HAND : Card::PLACE_TABLE;

	if( isYaku )
	{
		for( int i = 0; i < mYakuCards.getSize(); i++ )
		{
			if( mYakuCards[i]->getPlace() == place )
			{
				strongest = mYakuCards[i]->getNumber();
				break;
			}
		}
	}
	else
	{
		for( int i = 0; i < mNotYakuCards.getSize(); i++ )
		{
			if( mNotYakuCards[i]->getPlace() == place )
			{
				strongest = mNotYakuCards[i]->getNumber();
				break;
			}
		}
	}

	return strongest;
}

void Yaku::winGame()
{
	if( mYaku == YAKU_HIGHCARD )
	{
		mNotYakuCards[0]->win();
	}
	else
	{
		int size = mYakuCards.getSize();
		for( int i = 0; i < size; i++ )
		{
			mYakuCards[i]->win();
		}
	}
}
