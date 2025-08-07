#include "stdafx.h"	//※<sstream>の前にincludeしないと<sstream>が使えない
					// cppの先頭で呼び出さないと他にも色々と不都合が起こる
#include "ActionMenuMediator.h"
#include "WordConverter.h"
#include "VValue.h"
#include <sstream>
#include <cassert>

#define MENU_BET 0
#define MENU_CALL 1
#define MENU_FOLD 2
#define MENU_ALLIN 3

ActionMenuMediator* ActionMenuMediator::mInstance = 0;

ActionMenuMediator::ActionMenuMediator(void): mAction( 0 ), mInput( 0 ), mMenuSize( MENUSIZE_MAX )
{
	for( int i = 0; i < MENUSIZE_MAX; i++ )
	{
		mChoices[i] = Action::CHOICE_NONE;
	}
}

ActionMenuMediator::~ActionMenuMediator(void)
{
}

void ActionMenuMediator::create()
{
	if( mInstance ) return;

	mInstance = new ActionMenuMediator();
} 

void ActionMenuMediator::destroy()
{
	if( mInstance ) delete( mInstance );
	mInstance = 0;
}

ActionMenuMediator* ActionMenuMediator::instance()
{
	return mInstance;
}

void ActionMenuMediator::addRefObject( Action* ac )
{
	mAction = ac;
}


bool ActionMenuMediator::setInput( int inputOrg )
{
	// 表示上の番号は＋１されているため－１する
	int input = inputOrg - 1;
	// 範囲外
	if( input < 0 || MENUSIZE_MAX <= input )
	{
		return false;
	}
	// 無効な選択肢
	if( mChoices[input] == Action::CHOICE_NONE )
	{
		return false;
	}
	mInput = input;
	return true;
}

VValueSet ActionMenuMediator::getValue( ActionValue aValue )
{
	VValueSet atSet;
	VValue at;

	switch( aValue )
	{
	case ACTION_MENU:
		updateMenu();
		for( int i = 0; i < mMenuSize; i++ )
		{
			at.setValue( getMenu( i ) );
			atSet.addVValue( at );
		}
		break;
	default:
		break;
	}

	return atSet;
}

Action::Choice ActionMenuMediator::getInput() const
{
	assert( 0 <= mInput && mInput < MENUSIZE_MAX );
	return mChoices[mInput];
}

string ActionMenuMediator::getSelectMenu() const
{
	assert( 0 <= mInput && mInput < MENUSIZE_MAX );
	return WordConverter::convertChoice( mChoices[mInput] );
}

void ActionMenuMediator::updateMenu()
{
	mInput = 0;

	for( int i = 0; i < MENUSIZE_MAX; i++ )
	{
		mChoices[i] = Action::CHOICE_NONE;
	}

	if( mAction->isPossible( Action::CHOICE_BET ) )
	{
		mChoices[MENU_BET] = Action::CHOICE_BET;
	}
	else if( mAction->isPossible( Action::CHOICE_RAISE ) )
	{
		mChoices[MENU_BET] = Action::CHOICE_RAISE;
	}

	if( mAction->isPossible( Action::CHOICE_CALL ) )
	{
		mChoices[MENU_CALL] = Action::CHOICE_CALL;
	}
	else if( mAction->isPossible( Action::CHOICE_CHECK ) )
	{
		mChoices[MENU_CALL] = Action::CHOICE_CHECK;
	}

	mChoices[MENU_FOLD] = Action::CHOICE_FOLD;

	if( mAction->isPossible( Action::CHOICE_ALLIN ) )
	{
		mChoices[MENU_ALLIN] = Action::CHOICE_ALLIN;
	}

}

string ActionMenuMediator::getMenu( int idx ) const
{
	assert( 0 <= idx && idx < MENUSIZE_MAX );

	if( mChoices[idx] == Action::CHOICE_NONE )
	{
		return "";
	}

	// 「1 : ベット」という形式に整形
	ostringstream oss;
	oss << idx + 1 << " : ";
	oss << WordConverter::convertChoice( mChoices[idx] );
	if( mChoices[idx] == Action::CHOICE_BET
		|| mChoices[idx] == Action::CHOICE_RAISE )
	{
		oss << "  "  << WordConverter::toString( mAction->getCurrentBet() );
	}

	return oss.str();
}