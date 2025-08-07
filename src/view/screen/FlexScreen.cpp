#include "FlexScreen.h"
#include "Row.h"
#include "Col.h"
#include "VValue.h"
#include "Element.h"
#include "Attribute.h"
#include <cassert>

FlexScreen::FlexScreen( const Element* e ): mRows( 0 ), mRowNum( 0 )
{
	int atSize = e->getAttributeSize();
	const Attribute* at = e->getAttribute( Attribute::ROWSIZE );

	mRowNum = at->getIntValue();

	mRows = new Row*[mRowNum];
	for( int i = 0; i < mRowNum; i++ )
	{
		mRows[i] = new Row( e->getChild( i ), this );
	}
}

FlexScreen::~FlexScreen(void)
{
	for( int i = 0; i < mRowNum; i++ )
	{
		delete( mRows[i] );
	}
	delete[]( mRows );
}

void FlexScreen::draw()
{
	for( int i = 0; i < mRowNum; i++ )
	{
		mRows[i]->draw();
	}
}

void FlexScreen::update( string key, const VValue& vvalue )
{
	mCols[key]->setValue( vvalue );
}

void FlexScreen::update( string key, const VValue& vvalue, Format::StrColor color )
{
	mCols[key]->setValue( vvalue );
	setOneTimeColor( key, color );
}

void FlexScreen::update( string key, string value )
{
	mCols[key]->setValue( value );
}

void FlexScreen::update( string key, string value, Format::StrColor color )
{
	mCols[key]->setValue( value );
	setOneTimeColor( key, color );
}

void  FlexScreen::clear()
{
	for( int i = 0; i < mRowNum; i++ )
	{
		mRows[i]->clear();
	}
}

void FlexScreen::clearRow( int row )
{
	assert( 0 <= row && row < mRowNum );
	mRows[row]->clear();
}

void FlexScreen::clearCol( string key )
{
	mCols[key]->clear();
}

Format* FlexScreen::getFormat( string key )
{
	return mCols[key]->getFormat();
}

void FlexScreen::setOneTimeColor( string key, Format::StrColor color )
{
	Format* f = getFormat( key );
	f->mOneTimeColor = color;
}

void FlexScreen::addCol( string key, Col* col )
{
	mCols[key] = col;
}
