#include "GameBuilder.h"
#include "TableCard.h"
#include "Dealer.h"
#include "Player.h"
#include "CardPack.h"
#include "AutoDecision.h"
#include "ManualDecision.h"
#include "YakuHantei2.h"
#include "YakuHantei5.h"
#include "Action.h"
#include "Bet.h"
#include "PotDistribution.h"
#include "CardManager.h"
#include "NTimesMatch.h"
#include "SurvivalMatch.h"
#include "ActionMenuMediator.h"
#include "DealerMediator.h"
#include "PlayerMediator.h"
#include "TableCardMediator.h"
#include "MatchConditionMediator.h"
#include "Config.h"
#include "MyMacro.h"
#include <string>
#include <cassert>

using namespace std;

static string gNames[] = { "", "ロイド", "ソアラ", "マリア" };

GameBuilder::GameBuilder( const Config* con ): mConfig( con ), mDealer( 0 ), mTableCard( 0 )
												, mYakuHantei2( 0 ), mYakuHantei5( 0 ), mMatchCondition( 0 )
{
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		mPlayers[i] = 0;
	}

	build();
}

GameBuilder::~GameBuilder(void)
{
	ActionMenuMediator::destroy();
	DealerMediator::destroy();
	PlayerMediator::destroy();
	TableCardMediator::destroy();
	MatchConditionMediator::destroy();
	SAFE_DELETE( mDealer );
	for( int i = 0; i < mConfig->getPlayerNum(); i++ )
	{
		SAFE_DELETE( mPlayers[i] );
	}
	SAFE_DELETE( mTableCard );
	SAFE_DELETE( mYakuHantei2 );
	SAFE_DELETE( mYakuHantei5 );

}

void GameBuilder::build()
{
	createTableCard();
	createDealer();
	createPlayer();

	for( int i = 0; i < mConfig->getPlayerNum(); i++ )
	{
		mDealer->addPlayer( mPlayers[i] );
		mMatchCondition->addPlayer( mPlayers[i] );
	}
	mDealer->initialize( mConfig );
	mMatchCondition = 0;
}

void GameBuilder::createTableCard()
{
	mTableCard = new TableCard();

	TableCardMediator::create();
	TableCardMediator::instance()->addRefObject( mTableCard );
}

void GameBuilder::createDealer()
{
	CardManager* manager = new CardManager();
	Bet* bet = new Bet( mConfig->getBet() );
	Action* action = new Action( bet );
	PotDistribution* pot = new PotDistribution();
	switch( mConfig->getGameRule() )
	{
	case Config::GR_NTIMES:
		mMatchCondition = new NTimesMatch( mConfig );
		break;
	case Config::GR_SURVIVAL:
		mMatchCondition = new SurvivalMatch( mConfig );
		break;
	}
	mDealer = new Dealer( manager, mTableCard, action, pot, mMatchCondition ) ;

	ActionMenuMediator::create();
	ActionMenuMediator::instance()->addRefObject( action );
	DealerMediator::create();
	DealerMediator::instance()->addRefObject( mDealer );
	MatchConditionMediator::create();
	MatchConditionMediator::instance()->addRefObject( mMatchCondition );
}

void GameBuilder::createPlayer()
{
	ManualDecision* mDecision = new ManualDecision();
	 mYakuHantei2 = new  YakuHantei2();
	 mYakuHantei5 = new  YakuHantei5();

	CardPack* cp = new CardPack( mTableCard );
	cp->addYakuHantei(  mYakuHantei2 );
	cp->addYakuHantei(  mYakuHantei5 );
	mPlayers[0] = new Player( mConfig->getName(), cp, mDecision ); 

	for( int i = 1 ; i < mConfig->getPlayerNum(); i++ )
	{
		AutoDecision* aDecision = new AutoDecision( mDealer );
		cp = new CardPack( mTableCard );
		cp->addYakuHantei(  mYakuHantei2 );
		cp->addYakuHantei(  mYakuHantei5 );
		mPlayers[i] = new Player( gNames[i], cp, aDecision ); 
	}

	PlayerMediator::create();
	for( int i = 0; i < mConfig->getPlayerNum(); i++ )
	{
		 PlayerMediator::instance()->addRefObject( mPlayers[i] );
	}
}

Dealer* GameBuilder::getDealer()
{
	return mDealer;
}
