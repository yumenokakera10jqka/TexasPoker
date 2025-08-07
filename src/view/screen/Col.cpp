#include "Col.h"
#include "FlexScreen.h"
#include "Element.h"
#include "Attribute.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <ios>

Col::Col( const Element* e, FlexScreen* fs )
{
	int atSize = e->getAttributeSize();
	const Attribute* atName = e->getAttribute( Attribute::NAME );
	mName = atName->getValue();
	fs->addCol( mName, this );

	const Attribute* atWidth = e->getAttribute( Attribute::WIDTH );
	mFormat.mWidth = atWidth->getIntValue();

	const Attribute* atAlign = e->getAttribute( Attribute::ALIGN );
	string align = atAlign->getValue();
	if( align == "left" )
	{
		mFormat.mAlign = Format::ALIGN_LEFT;
	}
	else if( align == "right" )
	{
		mFormat.mAlign = Format::ALIGN_RIGHT;
	}
}

Col::Col()
{
}

Col::~Col(void)
{
}

void Col::setValue( const VValue& value )
{
	mVValue = value;
}

void Col::setValue( string value )
{
	mVValue.setValue( value );
}

void Col::draw()
{
	/*
	Format::StrColor color = mVValue.getColor();
	if( color != Format::COLOR_NONE )
	{
		mFormat.mOneTimeColor = color;
	}
*/
	mFormat.draw( mVValue );
}

void Col::setFormat( Format f )
{
	mFormat = f;
}

Format* Col::getFormat()
{
	return &mFormat;
}

int Col::getWidth() const
{
	return mFormat.mWidth;
}

void Col::clear()
{
	mVValue.clear();
}
