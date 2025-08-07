#pragma once
#include "Constants_Game.h"
#include "SortArray.h"
#include "Card.h"

class Yaku
{
public:
	Yaku(void);
	~Yaku(void);

	// 役の種類
	enum YakuSet{
		YAKU_HIGHCARD,
		YAKU_ONEPAIR,
		YAKU_TWOPAIR,
		YAKU_THREECARD,
		YAKU_STRAIGHT,
		YAKU_FLUSH,
		YAKU_FULLHOUSE,
		YAKU_FORECARD,
		YAKU_STRAIGHTFLUSH,
		YAKU_ROYALSTRAIGHTFLUSH,
		YAKU_SIZE
	};

	bool operator>( const Yaku& ) const;
	bool operator<( const Yaku& ) const;
	bool operator==( const Yaku& ) const;

	void setYaku( YakuSet );
	YakuSet getYaku() const;
	// 役カードを強い順に並べ替えてセットする
	void addYakuCard( Card* );
	const Card* getYakuCard( int ) const;
	int getYakuCardNum() const;
	// 非役カードを強い順に並べ替えてセットする
	void addNotYakuCard( Card* );
	const Card* getNotYakuCard( int ) const;
	int getNotYakuCardNum() const;
	void reset();
	// 役カードのなかのハンドカードの枚数
	int handNumInYaku() const;	
	/* 引数で指定した条件のもと最強のカードの数字を返す
		isYaku	役カードの場合true 非役カードの場合false
		isHand	ハンドカードの場合true テーブルカードの場合false */
	int strongestCardNum( bool isYaku, bool isHand ) const; 
	void winGame();

private:
	YakuSet mYaku;
	/* 役カード													
		＝ハンドカードとテーブルカードのうち役を構成するカード */
	SortArray<Card> mYakuCards;
	/* 非役カード
		＝ハンドカードとテーブルカードのうち役を構成しないカード */
	SortArray<Card> mNotYakuCards;
};
