#pragma once
#include "Constants_Game.h"
#include "VValueSet.h"

class Player;

class PlayerMediator
{
	friend class PlayerMediatorTest;
public:
	enum PlayerIdx
	{
		PLAYER_MAN,
		PLAYER_CPU,
		PLAYER_NONE
	};

	enum PlayerValue
	{
		PLAYER_NAME,
		PLAYER_CHIP,
		PLAYER_STACKCHIP,
		PLAYER_HAND,
		PLAYER_ACTION,
		PLAYER_ACTIVE,
		PLAYER_WIN,
		PLAYER_YAKU
	};

	static void create();
	static void destroy();
	static PlayerMediator* instance();

	// �O��F����v���C���[���ŏ��ɉ����A�ȍ~�͍��ׂ�CPU�����Ԃɉ�����
	void addRefObject( Player* );
	// ���𓾂����v���C���[��ݒ肷��
	void selectPlayer( PlayerIdx );
	// ���𓾂����v���C���[�����ɂ����߂�
	bool next();
	int getPlayerNum() const;
	VValueSet getValue( PlayerValue ) const;

private:
	PlayerMediator(void);
	~PlayerMediator(void);
	PlayerMediator( const PlayerMediator& );
	void operator =( const PlayerMediator& );

	static PlayerMediator* mInstance;
	int mPlayerNum;
	Player* mPlayers[PLAYER_MAX];
	PlayerIdx mSelectedPlayer;	// ����v���C���[�ACPU�̂ǂ���̏��𓾂邩
	int mCurrentPlayer;	// ���𓾂�v���C���[�̃C���f�b�N�X
};
