#pragma once
#include "Constants_Game.h"

class Card;

class CardSetIterator
{

typedef unsigned combi;

public:
	CardSetIterator( int );
	~CardSetIterator(void);

	void setCard( Card* );
	int getCardNum() const;
	int getSelectNum() const;
	// ハンドカードとテーブルカードから指定枚数を選択し先頭に並べ替えて返す
	// カード枚数が選択枚数を超えている場合、選択されたカードの後に選択されなかったカードが並ぶ
	// 並び順はソートされない
	Card** getNextSet();	

	// イテレータはコピーして返す（newすると使用者がdeleteする手間あり）
	// その際コピーコンストラクタを作らないと、①配列のアドレスがコピーされ
	// ②コピー元を作った関数終了とともにコピー元破棄 = コピーされたアドレスも破棄されてしまう
	// スマートポインタを使う方法（最良）や、イテレータ生成クラスが配列をもっておくという手もある（結合強）
	CardSetIterator( const CardSetIterator& );
	CardSetIterator& operator=( const CardSetIterator& );

private:
	Card* mCards[CARDSET_MAX];
	Card* mCardSet[CARDSET_MAX];
	int mCardNum;	// 全体のカード枚数
	int mSelectNum;	// 選択するカード枚数
	combi mCombi;	// 選んだカードをビットで表している（選ばれた=1,選ばれなかった=0）
};
