#include "SelectMenu.h"
#include "Constants_View.h"
#include <iostream>
#include <cassert>

#define SELECTMENU_MSG_INPUTURGE "選択肢の番号を半角数字で入力してください"
#define SELECTMENU_MSG_INPUTNG "入力が不正です。選択肢の番号を半角数字で入力してください"

SelectMenu::SelectMenu( int wordMax ): mWords( 0 ),mWordMax( wordMax ), mWordNum( 0 ), mResponse( INT_MIN )
{
	mWords = new string[wordMax];
}

SelectMenu::~SelectMenu(void)
{
	delete[]( mWords );
}

void SelectMenu::addWord( string word )
{
	assert( mWordNum < mWordMax );
	mWords[mWordNum++] = word; 
}

void SelectMenu::draw()
{
	mResponse = INT_MIN;

	cout << WORD_KEISEN << endl << endl;

	for( int i = 0; i < mWordNum; i++ )
	{
		cout << i+1 << "：" << mWords[i] << endl;
	}

	cout << endl << WORD_KEISEN;

	cout << endl;
	cout << SELECTMENU_MSG_INPUTURGE << endl;

	while( true )
	{
		cin >> mResponse;
		if( 1 <= mResponse && mResponse <= mWordNum )
		{
			mResponse--;
			break;
		}
		cout << SELECTMENU_MSG_INPUTNG << endl;
	}
}

int SelectMenu::getInput() const
{
	assert( mResponse != INT_MIN );
	return mResponse;
}
