#pragma once
#include "Constants_Game.h"
#include "CardSetIterator.h"
#include "Yaku.h"
#include <map>

class Card;
class TableCard;
class YakuHantei;

using namespace std;

// ハンドカードとテーブルカードから役を作るクラス
class CardPack
{
public:
	friend class CardPackTest;

	CardPack( TableCard* );
	virtual ~CardPack(void);

	// 現在のハンドカードとテーブルカードから最強の役を作る
	virtual void addYakuHantei( YakuHantei* );
	virtual void setHand( Card* );
	virtual void updateYaku();
	void openHand();
	virtual const Yaku& getYaku() const;
	virtual void reset();
	const Card& getHand( int ) const;
	int getHandNum() const;
	int getTableCardNum() const;
	void winGame();

private:
	CardSetIterator createIterator();

	Card* mHands[HANDCARD_MAX];
	int mHandNum;	// ハンドカードの枚数
	TableCard* mTable;	// テーブルカード。基本的に参照のみ
	Yaku mYaku;	// 自分が作れる最強の役
	map<int, YakuHantei*> mYakuHantei;
};
