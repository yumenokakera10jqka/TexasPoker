#include "VValue.h"
#include <cassert>

VValue::VValue(void): mValue( "" )
{
}

VValue::~VValue(void)
{
}

void VValue::setValue( string value )
{
	mValue = value;
}

void VValue::setColor( Format::StrColor color )
{
	mFormat.mOneTimeColor = color;
}

string VValue::getValue() const
{
	return mValue;
}

Format::StrColor VValue::getColor() const
{
	return mFormat.mOneTimeColor;
}

void VValue::clear()
{
	mValue = "";
	mFormat.reset();
}

Format* VValue::getFormat()
{
	return &mFormat;
}

void VValue::draw()
{
	mFormat.draw( mValue );
}
