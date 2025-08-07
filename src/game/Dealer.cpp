#include "Dealer.h"
#include "Player.h"
#include "CardManager.h"
#include "TableCard.h"
#include "PotDistribution.h"
#include "MatchCondition.h"
#include "Card.h"
#include "MyMacro.h"
#include "Config.h"
#include "MyRandom.h"
#include <cassert>
#include <algorithm>	//qsort

#ifndef TEST_DEALER
	#define FUNC_NEXTPLAYERINDEX nextPlayerIndex
	#define	FUNC_ISROUNDFINISHED isRoundFinished
	#define	FUNC_CALCDISTANCE calcDistance
	#define	FUNC_ISGAMEFINISHED isGameFinished
#endif

static int CompPlayer(const void* pElem1, const void* pElem2)
{
    // pElem1 はポインタ（渡した配列の要素）へのポインタ
    const Player* pmem1 = *(const Player**)pElem1;
    const Player* pmem2 = *(const Player**)pElem2;
	const Player& p1 = *pmem1;
	const Player& p2 = *pmem2;

	if( p1 < p2 )
	{
		return 1;
	}

    return -1;
}

using namespace std;

Dealer::Dealer( CardManager* cm, TableCard* tc, Action* a, PotDistribution* pd, MatchCondition* mc ):
				mCardManager( cm ), mTable( tc ), mAction( a ), mPotDistribution( pd ), mMatchCondition( mc )
				, mPlayerNum( 0 ), mCurrentPlayer( 0 ), mRestPlayerNum( 0 ), mRound( 0 )
				, mButton( 0 ), mGameNum( 0 ), mParticipantNum( 0 ), mCardNumToPlayer( 0 ), mRoundMax( 0 )
{
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mPlayers[i] = 0;
		mParticipants[i] = 0;
	}
	for( int i = 0; i <= ROUND_MAX; i++ )
	{
		mCardNumToTable[i] = 0;
	}
}

Dealer::~Dealer(void)
{
	SAFE_DELETE( mCardManager );
	SAFE_DELETE( mAction );
	SAFE_DELETE( mPotDistribution );
	SAFE_DELETE( mMatchCondition );
}

void Dealer::initialize( const Config* con )
{
	mGameNum = 0;
	mButton = MyRandom::getRandom() % mParticipantNum;
	mPlayerNum = mParticipantNum;
	for( int i = 0; i < mParticipantNum; i++ )
	{
		mParticipants[i]->initialize( con );
		mPlayers[i] = mParticipants[i];
	}
	mMatchCondition->initialize( con );	
	mCardNumToPlayer = con->getCardNumToPlayer();
	mRoundMax = con->getRoundNum();
	int cardNumToTable[ROUND_MAX+1];
	con->getCardNumToTable( cardNumToTable );

	for( int i = 0; i <= mRoundMax; i++ )
	{
		mCardNumToTable[i] = cardNumToTable[i];
	}
}

void Dealer::prepareGame()
{
	assert( mPlayerNum > 1 );

	for( int i = 0; i < mPlayerNum; i++ )
	{
		mPlayers[i]->prepareGame();
	}
	mCardManager->initialize();
	mCardManager->reset();
	mCardManager->shuffle();
	mTable->reset();
	mAction->prepareGame();
	mRound = 0;
	mGameNum++;
	mRestPlayerNum = mPlayerNum;
	mButton = nextButton();
	FUNC_CALCDISTANCE();	//mButtonに依存しているのでmButtonを設定した後に呼び出す
}

void Dealer::prepareRound()
{
	for( int i = 0; i < mPlayerNum; i++ )
	{
		mPlayers[i]->prepareRound();
	}
	mAction->prepareRound();
	mRound++;
	mCurrentPlayer = currentPlayer();
}

int Dealer::getRound() const
{
	return mRound;
}

void Dealer::addPlayer( Player* player )
{
	assert( player != 0 );
	assert( mPlayerNum < PLAYER_MAX );
	assert( mParticipantNum < PLAYER_MAX );

	mPlayers[mPlayerNum++] = player;
	mParticipants[mParticipantNum++] = player;
}

void Dealer::cardToPlayer()
{
	cardToPlayer( mCardNumToPlayer );
}

void Dealer::cardToTable()
{
	cardToTable( mCardNumToTable[mRound] );
}

void Dealer::cardToPlayer( int num )
{
	for( int i = 0; i < num; i++ )
	{
		for( int j = 0; j < mPlayerNum; j++ )
		{
			mPlayers[j]->setCard( mCardManager->take() );
		}
	}
	mParticipants[MANUALPLAYER_INDEX]->cardOpen();//※操作プレイヤーのハンドカードを見えるようにする
}

void Dealer::cardToTable( int num )
{
	for( int i = 0; i < num; i++ )
	{
		mTable->setCard( mCardManager->take() );
	}
}

void Dealer::littleBlind()
{
	bool isContinue = rotate();
	assert( isContinue );
	updateCurrentPlayer( Action::CHOICE_LITTLEBLIND );
}

void Dealer::bigBlind()
{
	bool isContinue = rotate();
	assert( isContinue );
	updateCurrentPlayer( Action::CHOICE_BIGBLIND );
}

bool Dealer::isGameFinished() const
{
	return ( mRestPlayerNum == DEALER_GAMEEND_NUM );
}


// TODO:TEST
bool Dealer::rotate()
{
	Player* prev = mPlayers[mCurrentPlayer];
	Action::Choice prevChoice = prev->getChoice();

	//ラウンドのはじめはmCurrentPlayerはmButtonの位置なので
	//mButtonのプレイヤーを更新しないようにTURN_ACTIVEのプレイヤーのみを更新対象とする
	//（※ラウンドはじめにmCurrentPlayerをLITTLEBRINDの位置に設定しておけばこの条件分岐は不要だが、
	// rotateとは別の関数でsetTurnStateを呼び出してTURN_ACTIVEにしておかなければならない
	// TURN_ELIMINATED以外の設定はrotateに集約したいので却下）
	if( prev->getTurnState() == Player::TURN_ACTIVE )
	{
		if( prevChoice == Action::CHOICE_FOLD )
		{
			prev->setTurnState( Player::TURN_OUT );
			mRestPlayerNum--;
		}
		// 先に判定しないとBIGBLINDで0になった場合に処理されないので注意
		else if( prev->getChipAmount() == 0 )
		{
			prev->setTurnState( Player::TURN_PASS );
		}
		else if( prevChoice == Action::CHOICE_BIGBLIND )
		{
			prev->setTurnState( Player::TURN_YET );
		}
		else
		{
			int inPlayerIdx = getLastInPlayerIdx();
			if( inPlayerIdx != -1 )
			{
				prev->setTurnState( Player::TURN_PASS );
			}
			else
			{
				prev->setTurnState( Player::TURN_WAIT );
			}
		}

		// ターンが回ってくるプレイヤーが残り１人になった場合
		int inPlayerIdx = getLastInPlayerIdx();
		if( inPlayerIdx != -1 )
		{
			//そのプレイヤーのチップが揃っているならＰＡＳＳにする
			if( mPlayers[inPlayerIdx]->getStackChipAmount() == mAction->getStackChipAmount() )
			{
				mPlayers[inPlayerIdx]->setTurnState( Player::TURN_PASS );
			}
		}
	}

	// 1ゲーム終了条件を満たしているなら戻る
	if( FUNC_ISGAMEFINISHED() )
	{
		return false;
	}
	// ラウンド終了条件を満たしているなら戻る
	if( FUNC_ISROUNDFINISHED() )
	{
		return false;
	}

	// 次のプレイヤーを検索する
	mCurrentPlayer = FUNC_NEXTPLAYERINDEX();
	Player* currentPlayer = mPlayers[mCurrentPlayer];
	currentPlayer->setTurnState( Player::TURN_ACTIVE );	//TODO:TEST
	
	// 可能なアクションを設定する
	mAction->setPossible( currentPlayer );

	return true;
}

int Dealer::getLastInPlayerIdx() const
{
	int inPlayerNum = 0;
	int idx = -1;
	for( int i = 0; i < mPlayerNum; i++ )
	{
		Player::TurnState ts = mPlayers[i]->getTurnState();
		if( ts == Player::TURN_YET
			|| ts == Player::TURN_ACTIVE
			|| ts == Player::TURN_WAIT )
		{
			inPlayerNum++;
			idx = i;
		}
	}
	if( inPlayerNum == 1 )
	{
		return idx;
	}
	return -1;
}

void Dealer::updateCurrentPlayer()
{
	updateCurrentPlayer( Action::CHOICE_NONE );
}

void Dealer::updateCurrentPlayer( Action::Choice choice )
{
	Player* currentPlayer = mPlayers[mCurrentPlayer];

	// 選択アクションの場合
	if( choice == Action::CHOICE_NONE )
	{
		currentPlayer->update( mAction );
	}
	// 強制アクションの場合
	else
	{
		mAction->action( choice, currentPlayer );
	}
}


void Dealer::showDown()
{
	for( int i = 0; i < mPlayerNum; i++ )
	{
		mPlayers[i]->showDown();
	}
	mTable->showDown();
}

void Dealer::finishGame()
{
	Player* players[PLAYER_MAX];
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		players[i] = mPlayers[i];
	}

	// プレイヤーを強い順に並べ替える
	qsort( players, mPlayerNum, sizeof *players, CompPlayer );

	// 勝者確定
	players[0]->winGame();
	for( int i = 1; i < mPlayerNum; i++ )
	{
		if( !( *( players[i] ) == *( players[i - 1] ) ) )
		{
			break;
		}
		players[i]->winGame();
	}

	// チップ分配
	mPotDistribution->initialize( players, mPlayerNum, mAction->getBet() );
	mPotDistribution->distribute();
}

bool Dealer::isMatchFinish()
{
	return mMatchCondition->isMatchFinish( this );
}

void Dealer::eliminatePlayer()
{

	// 排除条件を満たしているプレイヤーに排除フラグをたてる
	int bet = mAction->getBet();
	for( int i = 0; i <  mParticipantNum; i++ )
	{
		if( mParticipants[i]->getTurnState() == Player::TURN_ELIMINATED )
		{
			continue;
		}
		if( mParticipants[i]->getChipAmount() < bet )
		{
			 mParticipants[i]->setTurnState( Player::TURN_ELIMINATED );
			 mParticipants[i]->prepareGame();
			 mParticipants[i]->prepareRound();
		}
	}

	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mPlayers[i] = 0;
	}

	// 排除されなかったプレイヤーを勝負する権利を持つプレイヤーとして登録する
	mPlayerNum = 0;
	for( int i = 0; i <  mParticipantNum; i++ )
	{
		if( mParticipants[i]->getTurnState() != Player::TURN_ELIMINATED )
		{
			mPlayers[mPlayerNum++] = mParticipants[i];
		}
	}

	assert( mPlayerNum > 0 );
}

bool Dealer::isRoundFinished() const
{
	if( FUNC_ISGAMEFINISHED() )
	{
		return true;
	}

	for( int i = 0; i < mPlayerNum; i++ )
	{
		Player::TurnState ts = mPlayers[i]->getTurnState();
		// ゲームに参加していないプレイヤーはとばす
		if( ts == Player::TURN_PASS
			|| ts == Player::TURN_OUT )
		{
			continue;
		}
		// 未行動のプレイヤーがいる場合
		if( ts == Player::TURN_YET )
		{
			return false;
		}
		// プレイヤーのスタックチップが揃っていない場合
		if( mPlayers[i]->getStackChipAmount() != mAction->getStackChipAmount() )
		{
			return false;
		}
	}
	return true;
}

int Dealer::nextPlayerIndex() const
{
	int next = -1;

	for( int i = 1; i < mPlayerNum; i++ )
	{
		next = ( mCurrentPlayer + i ) % mPlayerNum;
		
		if( mPlayers[next]->getTurnState() == Player::TURN_YET
			|| mPlayers[next]->getTurnState() == Player::TURN_WAIT )
		{
			break;
		}
	}
	assert( next != -1 );

	return next;
}

// メンバmPlayers,mPlayerNum,mButtonが設定されていることが前提
void Dealer::calcDistance()
{
	assert( mPlayerNum > 1 );

	int lbPos = ( mButton + 1 ) % mPlayerNum;
	for( int i = 0 ; i < mPlayerNum; i++ )
	{
		mPlayers[(lbPos + i) % mPlayerNum]->setPosition( i );
	}
}

int Dealer::nextButton() const
{
	int num = 1;
	int button = mButton;
	while( num < mParticipantNum )
	{
		button = ( button + 1 ) % mParticipantNum;
		if( mParticipants[button]->getTurnState() != Player::TURN_ELIMINATED )
		{
			break;
		}
		num++;
	}
	return button;
}

int Dealer::currentPlayer() const
{
	for( int i = 0; i < mPlayerNum; i++ )
	{
		if( mPlayers[i] == mParticipants[mButton] )
		{
			return i;
		}
	}
	assert( false );
	return -1;
}

const Player& Dealer::getParticipant( int idx ) const
{
	assert( 0 <= idx && idx < mParticipantNum );
	return *mParticipants[idx];
}

int Dealer::getParticipantNum() const
{
	return mParticipantNum;
}

const Action& Dealer::getAction() const
{
	return *mAction;
}

bool Dealer::isManualPlayer() const
{
	return ( mPlayers[mCurrentPlayer] == mParticipants[MANUALPLAYER_INDEX] );
}

int Dealer::getPot() const
{
	int total = 0;
	for( int i = 0; i < mPlayerNum; i++ )
	{
		total += mPlayers[i]->getStackChipAmount();
	}
	return total;
}

int Dealer::getGameNum() const
{
	return mGameNum;
}

bool Dealer::isRoundComplete() const
{
	return mRound >= mRoundMax;
}
