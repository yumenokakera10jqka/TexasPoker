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

	// ���𔻒肷��ΏۃJ�[�h���Z�b�g����
	void setCards( Card** srcCards );
	// �J�[�h�̖��𔻒肷��
	bool hantei();
	// ���茋�ʂ�Ԃ�
	const Yaku& getYaku() const;
	// �����̒S���J�[�h������Ԃ�
	int numInCharge() const;

private:
	void reset();

	SortArray<Card> mCards;	// src �������ɕ���ł��锻��Ώۂ̃J�[�h
	Yaku mYaku;	// dst �����

	bool mIsSet;
};
