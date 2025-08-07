#pragma once

class Player;
class Bet;

class Action
{
public:
	friend class ActionTest;

	Action( Bet* );
	virtual ~Action(void);

	//���ύX�����ꍇ�AWordConverter��gChoiceWords�����Ԃ��Ή�����悤�ɕύX����
	enum Choice
	{
		CHOICE_BET,
		CHOICE_RAISE,
		CHOICE_CALL,
		CHOICE_CHECK,
		CHOICE_FOLD,
		CHOICE_ALLIN,
		CHOICE_LITTLEBLIND,
		CHOICE_BIGBLIND,
		CHOICE_NONE
	};

	virtual void prepareGame();	// 1�Q�[�����ƂɊJ�n�O�ɌĂяo��
	virtual void prepareRound();	// ���E���h�J�n�O�ɖ���Ăяo��
	virtual void setPossible( Player* );	// �v���C���[�̏��Ԃ��Ƃɖ���Ăяo��
	virtual void action( Choice, Player* );	// �O��FisPossible��true��choice�ȊO�̓G���[

	virtual int getCurrentBet() const;
	virtual int getBet() const;
	virtual int getStackChipAmount() const;
	virtual bool isPossible( Choice ) const;
	void collect( Player*, int );
	bool haveChip( Player*, int ) const;	//�����̃`�b�v�������Ă��邩�ǂ���

private:
	void littleBlind( Player* );
	void bigBlind( Player* );
	void bet( Player* );	
	void call( Player* );	
	void fold( Player* );	
	void check( Player* );	
	void raise( Player* );	
	void allIn( Player* );	
	void resetPossible();

	bool haveStackChip( Player* ) const;	// ���̐ςݏグ�z�ɒB���邽�߂̃`�b�v�������Ă��邩�ǂ���
	bool isPossibleBet( Player* ) const;
	bool isPossibleRaise( Player* ) const;
	bool isPossibleCheck( Player* ) const;
	bool isPossibleCall( Player* ) const;
	bool isPossibleAllIn( Player* ) const;
	bool isPossibleFold( Player* ) const;
	bool isPossibleLittleBlind( Player* ) const;
	bool isPossibleBigBlind( Player* ) const;

	Bet* mBet;
	int mStackChip;	// ���݂̃R�[���z
	bool mPossible[CHOICE_NONE];	// ���Ԃ������Ă����v���C���[�̊e�A�N�V�������\���ǂ���
};
