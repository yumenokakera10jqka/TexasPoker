#include "stdafx.h"	//��<sstream>�̑O��include���Ȃ���<sstream>���g���Ȃ�
					// cpp�̐擪�ŌĂяo���Ȃ��Ƒ��ɂ��F�X�ƕs�s�����N����
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
	// �\����̔ԍ��́{�P����Ă��邽�߁|�P����
	int input = inputOrg - 1;
	// �͈͊O
	if( input < 0 || MENUSIZE_MAX <= input )
	{
		return false;
	}
	// �����ȑI����
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

	// �u1 : �x�b�g�v�Ƃ����`���ɐ��`
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