#pragma once
#include <string>
#include "Action.h"

using namespace std;

class CardPack;
class Decision;
class Card;
class Yaku;
class Config;

class Player
{
public:
	friend class PlayerTest;

	enum WinState
	{
		STATE_WIN,
		STATE_LOSE,
		STATE_NONE
	};

	enum TurnState
	{
		TURN_ACTIVE,		//�s����
		TURN_WAIT,			//�ҋ@��
		TURN_PASS,			//SHOWDOWN�҂��iALLIN�Abet�Acall�ȂǂŃ��E���h���Ƀ`�b�v��0�ɂȂ����ꍇ�j
							//�܂��͎����ȊO�̏������~��Ă��Ȃ��v���C���[���S��TURN_PASS�ɂȂ����ꍇ
		TURN_OUT,			//��������~�肽�iFOLD�j
		TURN_YET,			//���s��
		TURN_ELIMINATED		//�Q�����𕥂��Ȃ����߃Q�[�����珜�O���ꂽ���
	};

	Player( const string&, CardPack*, Decision* );
	virtual ~Player(void);

	void initialize( const Config* );
	virtual void update( Action* );	//TODO:�e�X�g
	virtual void setCard( Card* );
	virtual void prepareGame();	//TODO:�e�X�g
	virtual void prepareRound();	//TODO:�e�X�g
	virtual bool deposit( int );
	virtual bool withDraw( int );
	virtual bool stackChip( int );	//TODO:�e�X�g
	virtual bool popChip( int );	//TODO:�e�X�g
	virtual void gainChip( int );	//TODO:TEST
	virtual void setChoice( Action::Choice );
	virtual void winGame();
	virtual void loseGame();
	virtual void resetWinCount();
	virtual void setPosition( int );	//TODO:TEST
	virtual void cardOpen();
	virtual void setTurnState( TurnState );	//TODO:TEST
	virtual void showDown(); //TODO:TEST

	virtual string getName() const;	
	virtual int getChipAmount() const;
	virtual int getStackChipAmount() const;	//TODO:�e�X�g
	virtual int getBetChipAmount() const;	//TODO:�e�X�g
	virtual int getGainChipAmount() const; //TODO:TEST
	virtual Action::Choice getChoice() const;
	virtual int winCount() const;
	virtual int loseCount() const;
	virtual bool isWonThisGame() const;
	virtual WinState getWinState() const;	//TODO:TEST
	virtual int getPosition() const;	//TODO:TEST
	virtual const Card& getHand( int ) const;	//TODO:TEST
	virtual int getHandNum() const;	//TODO:TEST
	virtual TurnState getTurnState() const;	//TODO:TEST
	virtual const Yaku& getYaku() const; //TODO:TEST
	virtual bool isShowDown() const; //TODO:TEST

	virtual bool operator>( const Player& ) const;	//TODO:TEST
	virtual bool operator<( const Player& ) const;	//TODO:TEST
	virtual bool operator==( const Player& ) const;	//TODO:TEST

private:
	CardPack* mCardPack;
	Decision* mDecision;

	string mName; 
	int mChip;
	int mStackChip;
	int mBetChip;	//TODO:TEST
	int mGainChip;
	Action::Choice mChoice;
	int mPosition;	//TODO:TEST
	int mWinCount;
	int mLoseCount;
	WinState mWinState;
	bool mCardOpen;
	TurnState mTurnState;
	bool mShowDown;
};
