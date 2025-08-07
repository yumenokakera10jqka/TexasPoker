#pragma once
#include "Constants_Game.h"

class Card;

class TableCard
{

public:
	TableCard(void);
	~TableCard(void);

	void setCard( Card* );	// �J�[�h���e�[�u���ɂP�����Z�b�g����
	const Card& get( int ) const;	// �w�肵���ʒu�̃J�[�h��Ԃ�
	void getCards( Card** dst, int size );	// �擪����size���̃J�[�h��dst�ɃZ�b�g����
	void reset();	// �e�[�u��������������
	int getCardNum() const;	// �e�[�u���ɂ���J�[�h������Ԃ�
	void showDown();
	bool isShowDown() const;

private:
	Card* mCards[TABLECARD_MAX];	// �e�[�u���ɂ���J�[�h
	int mCardNum;	// �e�[�u���ɂ���J�[�h����
	bool mShowDown;
};
