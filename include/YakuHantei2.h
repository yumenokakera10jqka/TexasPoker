#pragma once
#include "YakuHantei.h"
#include "Card.h"
#include "SortArray.h"

#define YAKUHANTEI2_CARDNUM 2

class YakuHantei2: public YakuHantei
{
public:
	friend class YakuHantei2Test;

	YakuHantei2(void);
	~YakuHantei2(void);

	// 役を判定する対象カードをセットする
	void setCards( Card** srcCards );
	// カードの役を判定する
	bool hantei();
	// 判定結果を返す
	const Yaku& getYaku() const;
	// 自分の担当カード枚数を返す
	int numInCharge() const;

private:
	void reset();

	SortArray<Card> mCards;	// src 強い順に並んでいる判定対象のカード
	Yaku mYaku;	// dst 役情報

	bool mIsSet;
};
