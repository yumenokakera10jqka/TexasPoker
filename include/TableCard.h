#pragma once
#include "Constants_Game.h"

class Card;

class TableCard
{

public:
	TableCard(void);
	~TableCard(void);

	void setCard( Card* );	// カードをテーブルに１枚ずつセットする
	const Card& get( int ) const;	// 指定した位置のカードを返す
	void getCards( Card** dst, int size );	// 先頭からsize分のカードをdstにセットする
	void reset();	// テーブルを初期化する
	int getCardNum() const;	// テーブルにあるカード枚数を返す
	void showDown();
	bool isShowDown() const;

private:
	Card* mCards[TABLECARD_MAX];	// テーブルにあるカード
	int mCardNum;	// テーブルにあるカード枚数
	bool mShowDown;
};
