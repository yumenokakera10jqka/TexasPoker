#pragma once

class Player;
class Action;

class Bet
{
public:
	Bet( int );
	~Bet(void);

	void setAction( Action* );
	virtual void prepareGame();	// 1�Q�[�����ƂɊJ�n�O�ɌĂяo��
	virtual void prepareRound();	// ���E���h�J�n�O�ɖ���Ăяo��
	virtual	void bet( Player* );
	virtual	void raise( Player* );
	int bigBlind( Player* );
	int littleBlind( Player* );

	bool isPossibleBet( Player* ) const;
	bool isPossibleRaise( Player* ) const;
	bool isPossibleLittleBlind( Player* ) const;
	bool isPossibleBigBlind( Player* ) const;
	int getBet() const;
	int getBetOrg() const;

private:
	virtual int calcNextBet() const;
	int calcLittleBlindAmount() const;

	Action* mAction;
	int mBetOrg;	// �Q�[���X�^�[�g���̃x�b�g�z
	int mBet;	// �x�b�g�����ۂ̏�悹�z
	bool mBeted;	// �e���E���h�ɂ����ăx�b�g�ς��ǂ���
	bool mLittleBlinded;	// �ŏ��̃��E���h�ɂ����ă��g���u���C���h�ς݂��ǂ���
	bool mBigBlinded;	// �ŏ��̃��E���h�ɂ����ăr�b�O�u���C���h�ς݂��ǂ���
};
