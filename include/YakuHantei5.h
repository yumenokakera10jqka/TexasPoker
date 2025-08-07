#pragma once
#include "Constants_Game.h"
#include "YakuHantei.h"
#include "Card.h"
#include "SortArray.h"

#define YAKUHANTEI5_PAIRCOUNT_MAX 2

// カードセット→判定→結果の役取り出しという手順を守る
class YakuHantei5: public YakuHantei
{
public:
	friend class YakuHantei5Test;

	YakuHantei5(void);
	~YakuHantei5(void);

	// 役を判定する対象カード５枚をセットする
	// 強い順に並べ替え、かつ判定に使うデータを取得する
	void setCards( Card** srcCards );
	// カードの役を判定し結果を返す
	bool hantei();
	//TODO:あと１枚で役が成立するかを判定する
	// 対象はロイヤルストレートフラッシュ、フラッシュ、ストレート
	bool hanteiRiichi();
	// 判定結果を返す
	const Yaku& getYaku() const;
	// 自分の担当カード枚数を返す
	int numInCharge() const;

private:
	bool isRoyalStraightFlush();
	bool isStraightFlush();
	bool isFlush();
	bool isStraight();
	bool isForeCard();
	bool isFullHouse();
	bool isThreeCard();
	bool isTwoPair();
	bool isOnePair();
	bool setHighCard();	

	bool isRoyalStraightFlushRiichi();	// TODO	ロイヤルストレートフラッシュにリーチか判定
	bool isFlushRiichi();	// TODO	フラッシュにリーチか判定
	bool isStraightRiichi();	// TODO	ストレートにリーチか判定

	// 全てのカードを役を構成するカードとしてセットする
	void setYakuAllCard( Yaku::YakuSet );
	// 引数で指定された数字をもつカードのみ役を構成するカードとしてセットする
	void setYakuPairCard( Yaku::YakuSet, int, int );
	void reset();
	// カードを調べて役を判定する判断材料を取得する
	void analyze();

	//TODO:自動的に強い順に並ぶカードクラスを作るYakuクラスも並べ替えを行っている
	SortArray<Card> mCards;	// src 強い順に並んでいる判定対象のカード
	Yaku mYaku;	// dst 役情報

	bool mIsSet;	// 判定対象のカードが正常にセット済みである
	bool mIsRoyal;		// 判断材料
	bool mIsRenban;		// 判断材料
	bool mIsSingleSuit;	// 判断材料
	int mForePairNum;	// 判断材料
	int mThreePairNum;	// 判断材料
	int mPairCount;		// 判断材料
	int mPairNum[YAKUHANTEI5_PAIRCOUNT_MAX];	// 判断材料
};
