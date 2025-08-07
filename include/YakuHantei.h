#pragma once
#include "Yaku.h"

class Card;

// カードセット→判定→結果の役取り出しという手順を守る
class YakuHantei
{
public:
	YakuHantei(void){};
	virtual ~YakuHantei(void){};

	// 役を判定する対象カードをセットする
	virtual void setCards( Card** srcCards ) = 0;
	// カードの役を判定する
	virtual bool hantei() = 0;
	// あと１枚で役が成立するかを判定する
	virtual bool hanteiRiichi()
	{
		return false;
	}
	// 判定結果を返す
	virtual const Yaku& getYaku() const = 0;
	// 自分の担当カード枚数を返す
	virtual int numInCharge() const = 0;
};
