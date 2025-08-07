#include "Screen.h"
#include "Row.h"
#include "Col.h"
#include "VValue.h"
#include <cassert>

Screen::Screen( int row, int col ): mRows( 0 )  ,mRowNum( row ), mColNum( col )
{
	mRows = new Row*[mRowNum];
	for( int i = 0; i < mRowNum; i++ )
	{
		mRows[i] = new Row( mColNum );
		for( int j = 0; j < mColNum; j++ )
		{
			addCol( i, j );
		}
	}
}

Screen::~Screen(void)
{
	for( int i = 0; i < mRowNum; i++ )
	{
		delete( mRows[i] );
	}
	delete[]( mRows );
}

void Screen::addCol( int row, int col )
{
	Col* newCol = new Col();

	mRows[row]->addCol( newCol, col );
}

void Screen::draw()
{
	for( int i = 0; i < mRowNum; i++ )
	{
		mRows[i]->draw();
	}
}

void Screen::update( int row, int col, const VValue& v )
{
	(*mRows[row])[col]->setValue( v );
}

void Screen::update( int row, int col, string value )
{
	(*mRows[row])[col]->setValue( value );
}

void Screen::clearRow( int row )
{
	assert( 0 <= row && row < mRowNum );
	mRows[row]->clear();
}

void Screen::clearCol( int col )
{
	assert( 0 <= col && col < mColNum );
	for( int i = 0; i < mRowNum; i++ )
	{
		(*mRows[i])[col]->clear();
	}
}

Format* Screen::getFormat( int row, int col )
{
	return (*mRows[row])[col]->getFormat();
}

void Screen::setOneTimeColor( int row, int col, Format::StrColor color )
{
	Format* f = getFormat( row, col );
	f->mOneTimeColor = color;
}
