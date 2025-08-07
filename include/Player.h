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
		TURN_ACTIVE,		//行動中
		TURN_WAIT,			//待機中
		TURN_PASS,			//SHOWDOWN待ち（ALLIN、bet、callなどでラウンド中にチップが0になった場合）
							//または自分以外の勝負を降りていないプレイヤーが全員TURN_PASSになった場合
		TURN_OUT,			//勝負から降りた（FOLD）
		TURN_YET,			//未行動
		TURN_ELIMINATED		//参加料を払えないためゲームから除外された状態
	};

	Player( const string&, CardPack*, Decision* );
	virtual ~Player(void);

	void initialize( const Config* );
	virtual void update( Action* );	//TODO:テスト
	virtual void setCard( Card* );
	virtual void prepareGame();	//TODO:テスト
	virtual void prepareRound();	//TODO:テスト
	virtual bool deposit( int );
	virtual bool withDraw( int );
	virtual bool stackChip( int );	//TODO:テスト
	virtual bool popChip( int );	//TODO:テスト
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
	virtual int getStackChipAmount() const;	//TODO:テスト
	virtual int getBetChipAmount() const;	//TODO:テスト
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
