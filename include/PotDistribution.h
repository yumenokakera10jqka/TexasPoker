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
	// プレイヤー（メンバ）のスタックチップからスタックチップを徴収する
	// 第１引数：徴収対象プレイヤーの数
	// 第２引数：徴収額
	// 戻り値：合計徴収額
	int createMainPot( int, int );
	// プレイヤー（メンバ）の所持チップにメインポットから均等に分配する
	// 端数はlbに最も近いポジションのプレイヤーに分配する
	// 第１引数：分配対象プレイヤーの数
	// 第２引数：メインポット
	void distributeMainPot( int, int );
	int shortestPlayer( int ) const;
	// スタックチップが0のプレイヤーを引数の配列から取り除き前に詰める
	// 戻り値：取り除かれなかった人数
	int removeStackZeroPlayer( int );

	Player* mPlayers[PLAYER_MAX];
	int mPlayerNum;
	int mBet;
};
