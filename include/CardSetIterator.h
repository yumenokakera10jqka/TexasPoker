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
	// �n���h�J�[�h�ƃe�[�u���J�[�h����w�薇����I�����擪�ɕ��בւ��ĕԂ�
	// �J�[�h�������I�𖇐��𒴂��Ă���ꍇ�A�I�����ꂽ�J�[�h�̌�ɑI������Ȃ������J�[�h������
	// ���я��̓\�[�g����Ȃ�
	Card** getNextSet();	

	// �C�e���[�^�̓R�s�[���ĕԂ��inew����Ǝg�p�҂�delete�����Ԃ���j
	// ���̍ۃR�s�[�R���X�g���N�^�����Ȃ��ƁA�@�z��̃A�h���X���R�s�[����
	// �A�R�s�[����������֐��I���ƂƂ��ɃR�s�[���j�� = �R�s�[���ꂽ�A�h���X���j������Ă��܂�
	// �X�}�[�g�|�C���^���g�����@�i�ŗǁj��A�C�e���[�^�����N���X���z��������Ă����Ƃ����������i�������j
	CardSetIterator( const CardSetIterator& );
	CardSetIterator& operator=( const CardSetIterator& );

private:
	Card* mCards[CARDSET_MAX];
	Card* mCardSet[CARDSET_MAX];
	int mCardNum;	// �S�̂̃J�[�h����
	int mSelectNum;	// �I������J�[�h����
	combi mCombi;	// �I�񂾃J�[�h���r�b�g�ŕ\���Ă���i�I�΂ꂽ=1,�I�΂�Ȃ�����=0�j
};
