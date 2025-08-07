#pragma once

class Player;
class Bet;

class Action
{
public:
	friend class ActionTest;

	Action( Bet* );
	virtual ~Action(void);

	//※変更した場合、WordConverterのgChoiceWordsも順番が対応するように変更する
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

	virtual void prepareGame();	// 1ゲームごとに開始前に呼び出す
	virtual void prepareRound();	// ラウンド開始前に毎回呼び出す
	virtual void setPossible( Player* );	// プレイヤーの順番ごとに毎回呼び出す
	virtual void action( Choice, Player* );	// 前提：isPossibleがtrueのchoice以外はエラー

	virtual int getCurrentBet() const;
	virtual int getBet() const;
	virtual int getStackChipAmount() const;
	virtual bool isPossible( Choice ) const;
	void collect( Player*, int );
	bool haveChip( Player*, int ) const;	//引数のチップを持っているかどうか

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

	bool haveStackChip( Player* ) const;	// 次の積み上げ額に達するためのチップを持っているかどうか
	bool isPossibleBet( Player* ) const;
	bool isPossibleRaise( Player* ) const;
	bool isPossibleCheck( Player* ) const;
	bool isPossibleCall( Player* ) const;
	bool isPossibleAllIn( Player* ) const;
	bool isPossibleFold( Player* ) const;
	bool isPossibleLittleBlind( Player* ) const;
	bool isPossibleBigBlind( Player* ) const;

	Bet* mBet;
	int mStackChip;	// 現在のコール額
	bool mPossible[CHOICE_NONE];	// 順番が周ってきたプレイヤーの各アクションが可能かどうか
};
