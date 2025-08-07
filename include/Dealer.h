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

	// 【必須】Dealer生成後、最初に全Playerを登録する
	// Dealerクラスは配列インデックス0に登録されたプレイヤーを操作プレイヤーと認識する
	void addPlayer( Player* );
	//※勝負の行程は（（既定ラウンド数消化→１ゲーム消化）×Ｎ回→既定ゲーム数消化→１マッチ消化
	// 【必須】マッチ開始ごとに呼び出す
	void initialize( const Config* );
	// 【必須】1ゲーム毎に最初に呼び出す
	void prepareGame();
	// 【必須】1ラウンド毎に最初に呼び出す
	void prepareRound();
	void cardToPlayer();
	void cardToTable();
	void cardToPlayer( int );
	void cardToTable( int );
	void littleBlind();
	void bigBlind();
	// return false=ラウンド終了 true=ラウンド継続
	// arg CHOICE_NONEの場合プレイヤーがアクションを選択する、それ以外の場合は強制アクション
	// 呼び出し側では①rotate()で（ラウンド最初のプレイヤーであっても）次のプレイヤーに順番をまわし
	// ②updateCurrentPlayer()でプレイヤーに行動させることを繰り返す
	bool rotate();
	void updateCurrentPlayer();
	void finishGame();
	void showDown();
	bool isMatchFinish();	//マッチ（一番大枠の勝敗条件）が終了する条件を満たしたかどうか
	void eliminatePlayer();	//チップ切れのプレイヤーを排除する

	virtual const Player& getParticipant( int ) const;
	int getParticipantNum() const;
	virtual const Action& getAction() const; 
	virtual int getRound() const;
	int getGameNum() const;	
	bool isGameFinished() const;	//１つのゲームが終了する条件を満たしたかどうか ※クラス内部でも呼び出される
	bool isManualPlayer() const;
	int getPot() const;
	bool isRoundComplete() const;	//既定数のラウンドを消化したかどうか

private:
	void updateCurrentPlayer( Action::Choice );	//行動順が回ってきたプレイヤーにアクションさせる
	int nextPlayerIndex() const;	//行動可能な次のプレイヤーインデックスを取得する
	bool isRoundFinished() const;	//１つのラウンドが終了する条件を満たしたかどうか
	void calcDistance();	//リトルブラインドの席位置からの距離を計算する
	int nextButton() const;	//mParticipantsのなかのボタンプレイヤーの位置
	int currentPlayer() const;//mPlayersのなかのボタンプレイヤーの位置。各ラウンドのmCurrentPlayerの初期位置となる
	int getLastInPlayerIdx() const;// ターンがまわってくる最後の１人のプレイヤーインデックス

	CardManager* mCardManager;
	TableCard* mTable;
	Action* mAction;
	PotDistribution* mPotDistribution;
	MatchCondition* mMatchCondition;

	//チップ切れでEliminateされた人を含むプレイヤー一覧、操作プレイヤーを最初の要素として以降は席順に並んでいる
	Player* mParticipants[PLAYER_MAX];
	int mParticipantNum;
	//チップ切れでEliminateされた人を含まないプレイヤー一覧、このプレイヤー達を対象にしてゲームが進行する
	Player* mPlayers[PLAYER_MAX];
	int mPlayerNum;
	int mCurrentPlayer;	//行動中のプレイヤー
	int mRestPlayerNum;	//勝負する権利を持つプレイヤーの人数（FOLDしていない）
	int mButton;	//ポジションがボタンのプレイヤーのインデックス。ここを起点に順番がまわる
	int mRound;	// 現在のラウンド数
	int mGameNum; //TODO:TEST 現在のゲーム数
	int mCardNumToPlayer;
	int mCardNumToTable[ROUND_MAX + 1];
	int mRoundMax;

};
