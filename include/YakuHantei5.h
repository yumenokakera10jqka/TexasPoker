#pragma once
#include "Constants_Game.h"
#include "YakuHantei.h"
#include "Card.h"
#include "SortArray.h"

#define YAKUHANTEI5_PAIRCOUNT_MAX 2

// �J�[�h�Z�b�g�����聨���ʂ̖����o���Ƃ����菇�����
class YakuHantei5: public YakuHantei
{
public:
	friend class YakuHantei5Test;

	YakuHantei5(void);
	~YakuHantei5(void);

	// ���𔻒肷��ΏۃJ�[�h�T�����Z�b�g����
	// �������ɕ��בւ��A������Ɏg���f�[�^���擾����
	void setCards( Card** srcCards );
	// �J�[�h�̖��𔻒肵���ʂ�Ԃ�
	bool hantei();
	//TODO:���ƂP���Ŗ����������邩�𔻒肷��
	// �Ώۂ̓��C�����X�g���[�g�t���b�V���A�t���b�V���A�X�g���[�g
	bool hanteiRiichi();
	// ���茋�ʂ�Ԃ�
	const Yaku& getYaku() const;
	// �����̒S���J�[�h������Ԃ�
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

	bool isRoyalStraightFlushRiichi();	// TODO	���C�����X�g���[�g�t���b�V���Ƀ��[�`������
	bool isFlushRiichi();	// TODO	�t���b�V���Ƀ��[�`������
	bool isStraightRiichi();	// TODO	�X�g���[�g�Ƀ��[�`������

	// �S�ẴJ�[�h������\������J�[�h�Ƃ��ăZ�b�g����
	void setYakuAllCard( Yaku::YakuSet );
	// �����Ŏw�肳�ꂽ���������J�[�h�̂ݖ����\������J�[�h�Ƃ��ăZ�b�g����
	void setYakuPairCard( Yaku::YakuSet, int, int );
	void reset();
	// �J�[�h�𒲂ׂĖ��𔻒肷�锻�f�ޗ����擾����
	void analyze();

	//TODO:�����I�ɋ������ɕ��ԃJ�[�h�N���X�����Yaku�N���X�����בւ����s���Ă���
	SortArray<Card> mCards;	// src �������ɕ���ł��锻��Ώۂ̃J�[�h
	Yaku mYaku;	// dst �����

	bool mIsSet;	// ����Ώۂ̃J�[�h������ɃZ�b�g�ς݂ł���
	bool mIsRoyal;		// ���f�ޗ�
	bool mIsRenban;		// ���f�ޗ�
	bool mIsSingleSuit;	// ���f�ޗ�
	int mForePairNum;	// ���f�ޗ�
	int mThreePairNum;	// ���f�ޗ�
	int mPairCount;		// ���f�ޗ�
	int mPairNum[YAKUHANTEI5_PAIRCOUNT_MAX];	// ���f�ޗ�
};
