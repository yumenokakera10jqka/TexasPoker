#include <windows.h>
#include "View.h"
#include "Constants_View.h"
#include "RivalScreen.h"
#include "PlayerScreen.h"
#include "TableScreen.h"
#include "ResultScreen.h"
#include "DealerMediator.h"
#include "MatchConditionMediator.h"
#include <iostream>
#include <cassert>

#define WORD_GAMESTART "�f�`�l�d"
#define WORD_ROUNDSTART "�q�n�t�m�c"
#define WINDOW_W 90
#define WINDOW_H 22

using namespace std;

View::View()
{
	createScreen();
	fixConsoleSize();
}

View::~View(void)
{
	map<ScreenName, ScreenOperator*>::iterator it;
	for( it = mScreens.begin() ; it != mScreens.end(); it++ ){
		delete( (*it).second );
		(*it).second = 0;
	}
}


void View::draw( ViewState state )
{
	mScreens[SCREEN_RIVALS]->draw( state );
	mScreens[SCREEN_TABLE]->draw( state );
	mScreens[SCREEN_PLAYER]->draw( state );

	getchar();
}

void View::drawResult()
{
	mScreens[SCREEN_RESULT]->draw( VST_NONE );
	getchar();
}

void View::drawGameStart()
{
	VValueSet atSet = DealerMediator::instance()->getValue( DealerMediator::DEALER_GAME );
	cout << "�y";
	cout << atSet.getVValue().getValue();
	cout << " �^ ";
	atSet = MatchConditionMediator::instance()->getValue( MatchConditionMediator::MATCH_GAMENUM );
	cout << atSet.getVValue().getValue();
	cout << " " << WORD_GAMESTART;
	cout << "�z";
	cout << endl;
	getchar();
}

void View::drawRoundStart()
{
	VValueSet atSet = DealerMediator::instance()->getValue( DealerMediator::DEALER_ROUND );
	cout << WORD_KEISEN << endl;
	cout << "�y";
	cout << atSet.getVValue().getValue() << " " << WORD_ROUNDSTART;
	cout << "�z";
	cout << endl;
	getchar();
}

void View::createScreen()
{
	RivalScreen* rs = new RivalScreen();
	mScreens[SCREEN_RIVALS] = rs;
	PlayerScreen* ps = new PlayerScreen();
	mScreens[SCREEN_PLAYER] = ps;
	TableScreen* ts = new TableScreen();
	mScreens[SCREEN_TABLE] = ts;
	ResultScreen* rst = new ResultScreen();
	mScreens[SCREEN_RESULT] = rst;
}

//�R���\�[���T�C�Y�ݒ�͂��̃v���Z�X�ł̂ݗL���B���[�U�[�̐ݒ�l�͈ێ������
void View::fixConsoleSize()
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_SCREEN_BUFFER_INFO info;
	if( GetConsoleScreenBufferInfo( hStdout, &info ) == 0 )
	{
		return;
	}
	COORD size = info.dwSize;
	if( info.dwSize.X < WINDOW_W )
	{
		size.X = WINDOW_W;
	}
	if( info.dwSize.Y < WINDOW_H )
	{
		size.Y = WINDOW_H;
	}
	if( SetConsoleScreenBufferSize( hStdout, size ) == 0 )
	{
		//���݂̃o�b�t�@�T�C�Y��菬�����ƃG���[�B�傫������Ƃ��ɂ����g��
		return;
	}
	SMALL_RECT rect = info.srWindow;
	rect.Right = rect.Left + WINDOW_W - 1;
	rect.Bottom = rect.Top + WINDOW_H - 1;
	if( SetConsoleWindowInfo( hStdout, true, &(rect) ) == 0 )
	{
		//���݂̃o�b�t�@�T�C�Y�𒴂���ƃG���[
		return;
	}
}
