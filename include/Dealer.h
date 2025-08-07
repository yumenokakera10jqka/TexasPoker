#pragma once
#include "Constants_Game.h"
#include "Action.h"
#include <string>

#define DEALER_GAMEEND_NUM	1
#define MANUALPLAYER_INDEX 0

using namespace std;

class Player;
class TableCard;
class CardManager;
class PotDistribution;
class MatchCondition;
class Config;

class Dealer
{
public:
	friend class DealerTest;

	Dealer( CardManager*, TableCard*, Action*, PotDistribution*, MatchCondition* );
	virtual ~Dealer(void);

	// �y�K�{�zDealer������A�ŏ��ɑSPlayer��o�^����
	// Dealer�N���X�͔z��C���f�b�N�X0�ɓo�^���ꂽ�v���C���[�𑀍�v���C���[�ƔF������
	void addPlayer( Player* );
	//�������̍s���́i�i���胉�E���h���������P�Q�[�������j�~�m�񁨊���Q�[�����������P�}�b�`����
	// �y�K�{�z�}�b�`�J�n���ƂɌĂяo��
	void initialize( const Config* );
	// �y�K�{�z1�Q�[�����ɍŏ��ɌĂяo��
	void prepareGame();
	// �y�K�{�z1���E���h���ɍŏ��ɌĂяo��
	void prepareRound();
	void cardToPlayer();
	void cardToTable();
	void cardToPlayer( int );
	void cardToTable( int );
	void littleBlind();
	void bigBlind();
	// return false=���E���h�I�� true=���E���h�p��
	// arg CHOICE_NONE�̏ꍇ�v���C���[���A�N�V������I������A����ȊO�̏ꍇ�͋����A�N�V����
	// �Ăяo�����ł͇@rotate()�Łi���E���h�ŏ��̃v���C���[�ł����Ă��j���̃v���C���[�ɏ��Ԃ��܂킵
	// �AupdateCurrentPlayer()�Ńv���C���[�ɍs�������邱�Ƃ��J��Ԃ�
	bool rotate();
	void updateCurrentPlayer();
	void finishGame();
	void showDown();
	bool isMatchFinish();	//�}�b�`�i��ԑ�g�̏��s�����j���I����������𖞂��������ǂ���
	void eliminatePlayer();	//�`�b�v�؂�̃v���C���[��r������

	virtual const Player& getParticipant( int ) const;
	int getParticipantNum() const;
	virtual const Action& getAction() const; 
	virtual int getRound() const;
	int getGameNum() const;	
	bool isGameFinished() const;	//�P�̃Q�[�����I����������𖞂��������ǂ��� ���N���X�����ł��Ăяo�����
	bool isManualPlayer() const;
	int getPot() const;
	bool isRoundComplete() const;	//���萔�̃��E���h�������������ǂ���

private:
	void updateCurrentPlayer( Action::Choice );	//�s����������Ă����v���C���[�ɃA�N�V����������
	int nextPlayerIndex() const;	//�s���\�Ȏ��̃v���C���[�C���f�b�N�X���擾����
	bool isRoundFinished() const;	//�P�̃��E���h���I����������𖞂��������ǂ���
	void calcDistance();	//���g���u���C���h�̐Ȉʒu����̋������v�Z����
	int nextButton() const;	//mParticipants�̂Ȃ��̃{�^���v���C���[�̈ʒu
	int currentPlayer() const;//mPlayers�̂Ȃ��̃{�^���v���C���[�̈ʒu�B�e���E���h��mCurrentPlayer�̏����ʒu�ƂȂ�
	int getLastInPlayerIdx() const;// �^�[�����܂���Ă���Ō�̂P�l�̃v���C���[�C���f�b�N�X

	CardManager* mCardManager;
	TableCard* mTable;
	Action* mAction;
	PotDistribution* mPotDistribution;
	MatchCondition* mMatchCondition;

	//�`�b�v�؂��Eliminate���ꂽ�l���܂ރv���C���[�ꗗ�A����v���C���[���ŏ��̗v�f�Ƃ��Ĉȍ~�͐ȏ��ɕ���ł���
	Player* mParticipants[PLAYER_MAX];
	int mParticipantNum;
	//�`�b�v�؂��Eliminate���ꂽ�l���܂܂Ȃ��v���C���[�ꗗ�A���̃v���C���[�B��Ώۂɂ��ăQ�[�����i�s����
	Player* mPlayers[PLAYER_MAX];
	int mPlayerNum;
	int mCurrentPlayer;	//�s�����̃v���C���[
	int mRestPlayerNum;	//�������錠�������v���C���[�̐l���iFOLD���Ă��Ȃ��j
	int mButton;	//�|�W�V�������{�^���̃v���C���[�̃C���f�b�N�X�B�������N�_�ɏ��Ԃ��܂��
	int mRound;	// ���݂̃��E���h��
	int mGameNum; //TODO:TEST ���݂̃Q�[����
	int mCardNumToPlayer;
	int mCardNumToTable[ROUND_MAX + 1];
	int mRoundMax;

};
