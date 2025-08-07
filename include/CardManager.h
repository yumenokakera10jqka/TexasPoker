#pragma once
#include "Card.h"

#define CARDMANAGER_CARDNUM 52

class CardManager
{
public:
	CardManager(void);
	~CardManager(void);

	void initialize();	// new後、必ず呼び出す
	void shuffle();	
	void reset();	//TODO:テスト
	Card* take();	// デッキの１番上からカードを１枚取る
	const Card& takeR( int ) const;	//HACK: テスト用そのうち削除

private:
	Card mCardsO[CARDMANAGER_CARDNUM];	// オリジナルのカードデッキ
	Card* mCards[CARDMANAGER_CARDNUM];	// オリジナルを並べ替えたカードデッキ
	int mTop;	// 並べ替えたカードデッキの現在の１番上

};
