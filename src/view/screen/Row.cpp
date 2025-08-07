#include "Row.h"
#include "Col.h"
#include "FlexScreen.h"
#include "Element.h"
#include "Attribute.h"
#include <cassert>
#include <iostream>

using namespace std;

Row::Row( const Element* e, FlexScreen* fs ): mCols( 0 ), mColNum( 0 )
{
	int atSize = e->getAttributeSize();
	const Attribute* at = e->getAttribute( Attribute::COLSIZE );

	mColNum = at->getIntValue();

	mCols = new Col*[mColNum];
	for( int i = 0; i < mColNum; i++ )
	{
		mCols[i] = new Col( e->getChild( i ), fs );
	}
}

Row::Row( int colNum ): mCols( 0 ), mColNum( colNum )
{
	mCols = new Col*[mColNum];
	for( int i = 0; i < mColNum; i++ )
	{
		mCols[i] = 0;
	}
}

Row::~Row(void)
{
	for( int i = 0; i < mColNum; i++ )
	{
		delete( mCols[i] );
	}
	delete[]( mCols );
}

void Row::addCol( Col* col, int idx )
{
	assert( col != 0 );
	assert( ( 0 <= idx && idx < mColNum ) );
	assert( mCols[idx] == 0 );

	mCols[idx] = col;
}

void Row::draw()
{	
	for( int i = 0; i < mColNum; i++ )
	{
		assert( mCols[i] != 0 );
		mCols[i]->draw();
	}
	cout << endl;
}

void Row::clear()
{
	for( int i = 0; i < mColNum; i++ )
	{
		assert( mCols[i] != 0 );
		mCols[i]->clear();
	}
}

Col* Row::operator[]( int idx )
{
	assert( ( 0 <= idx && idx < mColNum ) );
	assert( mCols[idx] != 0 );
	return mCols[idx];
}

