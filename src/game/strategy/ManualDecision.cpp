#include "ManualDecision.h"
#include "Yaku.h"
#include "Player.h"
#include "ActionMenuMediator.h"
#include "Action.h"
#include <cassert>
#
ManualDecision::ManualDecision(): mPlayer( 0 )
{
}

ManualDecision::~ManualDecision(void)
{
}

void ManualDecision::setPlayer( Player* player )
{
	mPlayer = player;
}

void ManualDecision::prepareRound()
{
}

void ManualDecision::decide( const Yaku& yaku, Action* action )
{
	action->action( ActionMenuMediator::instance()->getInput(), mPlayer );
}
