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

	// 前提：操作プレイヤーを最初に加え、以降は左隣のCPUを順番に加える
	void addRefObject( Player* );
	// 情報を得たいプレイヤーを設定する
	void selectPlayer( PlayerIdx );
	// 情報を得たいプレイヤーを次にすすめる
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
	PlayerIdx mSelectedPlayer;	// 操作プレイヤー、CPUのどちらの情報を得るか
	int mCurrentPlayer;	// 情報を得るプレイヤーのインデックス
};
