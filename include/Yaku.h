#pragma once
#include "Constants_Game.h"
#include "SortArray.h"
#include "Card.h"

class Yaku
{
public:
	Yaku(void);
	~Yaku(void);

	// ���̎��
	enum YakuSet{
		YAKU_HIGHCARD,
		YAKU_ONEPAIR,
		YAKU_TWOPAIR,
		YAKU_THREECARD,
		YAKU_STRAIGHT,
		YAKU_FLUSH,
		YAKU_FULLHOUSE,
		YAKU_FORECARD,
		YAKU_STRAIGHTFLUSH,
		YAKU_ROYALSTRAIGHTFLUSH,
		YAKU_SIZE
	};

	bool operator>( const Yaku& ) const;
	bool operator<( const Yaku& ) const;
	bool operator==( const Yaku& ) const;

	void setYaku( YakuSet );
	YakuSet getYaku() const;
	// ���J�[�h���������ɕ��בւ��ăZ�b�g����
	void addYakuCard( Card* );
	const Card* getYakuCard( int ) const;
	int getYakuCardNum() const;
	// ����J�[�h���������ɕ��בւ��ăZ�b�g����
	void addNotYakuCard( Card* );
	const Card* getNotYakuCard( int ) const;
	int getNotYakuCardNum() const;
	void reset();
	// ���J�[�h�̂Ȃ��̃n���h�J�[�h�̖���
	int handNumInYaku() const;	
	/* �����Ŏw�肵�������̂��ƍŋ��̃J�[�h�̐�����Ԃ�
		isYaku	���J�[�h�̏ꍇtrue ����J�[�h�̏ꍇfalse
		isHand	�n���h�J�[�h�̏ꍇtrue �e�[�u���J�[�h�̏ꍇfalse */
	int strongestCardNum( bool isYaku, bool isHand ) const; 
	void winGame();

private:
	YakuSet mYaku;
	/* ���J�[�h													
		���n���h�J�[�h�ƃe�[�u���J�[�h�̂��������\������J�[�h */
	SortArray<Card> mYakuCards;
	/* ����J�[�h
		���n���h�J�[�h�ƃe�[�u���J�[�h�̂��������\�����Ȃ��J�[�h */
	SortArray<Card> mNotYakuCards;
};
