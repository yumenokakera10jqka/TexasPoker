#include "stdafx.h"
#include "Format.h"
#include "VValue.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <ios>
#include <sstream>

Format::Format(void): mWidth( 0 ), mAlign( Format::ALIGN_LEFT ), mOneTimeColor( COLOR_NONE )
					, mFlagsSaved( cout.flags() ), mHConsole( GetStdHandle(STD_OUTPUT_HANDLE) )
					, mDeco( DECO_NONE )
{
}

Format::~Format(void)
{
}

void Format::draw( string value )
{
	preDraw();

	ostringstream oss;
	if( mDeco == DECO_SHARP )
	{
		oss << "#";
	}

	preColor();

	oss << value;
	//※coutをすると幅設定等のマニピュレータが失われるので1回でまとめて出力する
	cout << oss.str();

	postColor();

	postDraw();
}

void Format::draw( VValue& vv )
{
	preDraw();

	if( mAlign == Format::ALIGN_RIGHT )
	{
		cout.setf( ios::right, ios::adjustfield );
	}
	else if( mAlign == Format::ALIGN_LEFT )
	{
		cout.setf( ios::left, ios::adjustfield );
	}
	//※このマニピュレータは1回coutすると失われる
	cout << setw( mWidth );
	preColor();

	vv.draw();

	postColor();
	postDraw();
}

void Format::reset()
{
	mOneTimeColor = COLOR_NONE;
	mDeco = DECO_NONE;
}

void Format::preDraw()
{
	ios::fmtflags mFlagsSaved = cout.flags();
}

void Format::postDraw()
{
	SetConsoleTextAttribute( mHConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
	cout.flags( mFlagsSaved );
}

void Format::preColor()
{
	switch( mOneTimeColor )
	{
	case COLOR_RED:
		SetConsoleTextAttribute(mHConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		mOneTimeColor = COLOR_NONE;
		break;
	case COLOR_GREEN:
		SetConsoleTextAttribute(mHConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		mOneTimeColor = COLOR_NONE;
		break;
	case COLOR_BLUE:
		SetConsoleTextAttribute(mHConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		mOneTimeColor = COLOR_NONE;
		break;
	case COLOR_YELLOW:
		SetConsoleTextAttribute(mHConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		mOneTimeColor = COLOR_NONE;
		break;
	case COLOR_PINK:
		SetConsoleTextAttribute(mHConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		mOneTimeColor = COLOR_NONE;
		break;
	case COLOR_CYAN:
		SetConsoleTextAttribute(mHConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		mOneTimeColor = COLOR_NONE;
		break;
	default:
		break;
	}
}

void Format::postColor()
{
	SetConsoleTextAttribute( mHConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}
