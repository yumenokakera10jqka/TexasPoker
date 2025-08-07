#pragma once
#include "Constants_Game.h"
#include "CardSetIterator.h"
#include "Yaku.h"
#include <map>

class Card;
class TableCard;
class YakuHantei;

using namespace std;

// �n���h�J�[�h�ƃe�[�u���J�[�h����������N���X
class CardPack
{
public:
	friend class CardPackTest;

	CardPack( TableCard* );
	virtual ~CardPack(void);

	// ���݂̃n���h�J�[�h�ƃe�[�u���J�[�h����ŋ��̖������
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
	int mHandNum;	// �n���h�J�[�h�̖���
	TableCard* mTable;	// �e�[�u���J�[�h�B��{�I�ɎQ�Ƃ̂�
	Yaku mYaku;	// ����������ŋ��̖�
	map<int, YakuHantei*> mYakuHantei;
};
