#pragma once

class Player;
class Action;

class Bet
{
public:
	Bet( int );
	~Bet(void);

	void setAction( Action* );
	virtual void prepareGame();	// 1ゲームごとに開始前に呼び出す
	virtual void prepareRound();	// ラウンド開始前に毎回呼び出す
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
	int mBetOrg;	// ゲームスタート時のベット額
	int mBet;	// ベットした際の上乗せ額
	bool mBeted;	// 各ラウンドにおいてベット済かどうか
	bool mLittleBlinded;	// 最初のラウンドにおいてリトルブラインド済みかどうか
	bool mBigBlinded;	// 最初のラウンドにおいてビッグブラインド済みかどうか
};
