#pragma once
#include "Card.h"

#define CARDMANAGER_CARDNUM 52

class CardManager
{
public:
	CardManager(void);
	~CardManager(void);

	void initialize();	// new��A�K���Ăяo��
	void shuffle();	
	void reset();	//TODO:�e�X�g
	Card* take();	// �f�b�L�̂P�ԏォ��J�[�h���P�����
	const Card& takeR( int ) const;	//HACK: �e�X�g�p���̂����폜

private:
	Card mCardsO[CARDMANAGER_CARDNUM];	// �I���W�i���̃J�[�h�f�b�L
	Card* mCards[CARDMANAGER_CARDNUM];	// �I���W�i������בւ����J�[�h�f�b�L
	int mTop;	// ���בւ����J�[�h�f�b�L�̌��݂̂P�ԏ�

};
