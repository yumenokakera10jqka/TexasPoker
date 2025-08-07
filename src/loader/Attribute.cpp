#include "stdafx.h"
#include "Attribute.h"
#include <sstream>

using namespace std;

Attribute::Attribute():
mType( NONE ), mName( "" ), mValue( "" )
{
}

Attribute::~Attribute()
{
}

Attribute::Type Attribute::getType() const
{
	return mType;
}

void Attribute::setName( string name )
{
	mName = name;

	if( name == "name" )
	{
		mType = NAME;
	}
	else if( name == "rowsize" )
	{
		mType = ROWSIZE;
	}
	else if( name == "colsize" )
	{
		mType = COLSIZE;
	}
	else if( name == "width" )
	{
		mType = WIDTH;
	}
	else if( name == "align" )
	{
		mType = ALIGN;
	}
	else
	{
		mType = NONE;
	}
}

string Attribute::getName() const
{
	return mName;
}

void Attribute::setValue( string value )
{
	mValue = value;
}

string Attribute::getValue() const
{
	return mValue;
}

int Attribute::getIntValues( int* out, int size ) const
{
	istringstream iss( mValue );
	int c = 0;

	for( int i = 0; i < size; i++ )
	{
		iss >> out[i];

		if( iss.fail() )
		{
			break;
		}

		++c;
		iss.ignore( static_cast<streamsize>( mValue.size() ), ',' );
	}

	return c;
}

int Attribute::getUnsignedIntValues( unsigned* out, int size ) const
{
	istringstream iss( mValue );
	int c = 0;

	for( int i = 0; i < size; i++ )
	{
		iss >> out[i];

		if( iss.fail() )
		{
			break;
		}

		++c;
		iss.ignore( static_cast<streamsize>( mValue.size() ), ',' );
	}

	return c;
}

int Attribute::getDoubleValues( double* out, int size ) const
{
	istringstream iss( mValue );
	int c = 0;

	for( int i = 0; i < size; i++ )
	{
		iss >> out[i];

		if( iss.fail() )
		{
			break;
		}

		++c;
		iss.ignore( static_cast<streamsize>( mValue.size() ), ',' );
	}

	return c;
}

double Attribute::getDoubleValue() const
{
	istringstream iss( mValue );
	double d = 0.0;
	iss >> d;
	return d;
}

int Attribute::getIntValue() const
{
	istringstream iss( mValue );
	int i = 0;
	iss >> i;
	return i;
}

unsigned Attribute::getUnsignedValue() const
{
	istringstream iss( mValue );
	unsigned u = 0;
	iss >> u;
	return u;
}
