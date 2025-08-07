#pragma once

#define PLAYER_MAX 4

class Player;

class PotDistribution
{
public:
	friend class PotDistributionTest;

	PotDistribution(void);
	~PotDistribution(void);


	virtual void initialize( Player** strongOrder, int playerNum, int bet );
	virtual void distribute();

private:
	int winnerNum( int ) const;
	int lowestStack( int ) const;
	// �v���C���[�i�����o�j�̃X�^�b�N�`�b�v����X�^�b�N�`�b�v�𒥎�����
	// ��P�����F�����Ώۃv���C���[�̐�
	// ��Q�����F�����z
	// �߂�l�F���v�����z
	int createMainPot( int, int );
	// �v���C���[�i�����o�j�̏����`�b�v�Ƀ��C���|�b�g����ϓ��ɕ��z����
	// �[����lb�ɍł��߂��|�W�V�����̃v���C���[�ɕ��z����
	// ��P�����F���z�Ώۃv���C���[�̐�
	// ��Q�����F���C���|�b�g
	void distributeMainPot( int, int );
	int shortestPlayer( int ) const;
	// �X�^�b�N�`�b�v��0�̃v���C���[�������̔z�񂩂��菜���O�ɋl�߂�
	// �߂�l�F��菜����Ȃ������l��
	int removeStackZeroPlayer( int );

	Player* mPlayers[PLAYER_MAX];
	int mPlayerNum;
	int mBet;
};
