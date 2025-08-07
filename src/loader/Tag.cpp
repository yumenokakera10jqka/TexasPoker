#include "stdafx.h"
#include "Tag.h"
#include "Attribute.h"
#include "MyMacro.h"

Tag::Tag()
{
	mName = "root";
}

Tag::Tag( const char** c ):
mType( NONE ), mName( "" ), mAttributes( 0 ),mAttributeSize( 0 )
{
	Sequence seq = SEQ_0;

	bool finish = false;
	std::string atrName = "";
	std::string atrValue = "";

	while( **c != '\0' )
	{
		switch( seq )
		{
		case SEQ_0:
			if( **c == '<' )
			{
				seq = SEQ_1;
			}
			break;
		case SEQ_1:
			if( **c == '/' )
			{
				mType = END_TAG;
				seq = SEQ_7;
			}
			else if( isGeneralChar( **c ) )
			{
				mType = START_TAG;
				mName = **c;
				seq = SEQ_2;
			}
			break;
		case SEQ_2:
			if( isGeneralChar( **c ) )
			{
				mName += **c;
			}
			else if( **c == ' ' )
			{
				seq = SEQ_3;
			}
			break;
		case SEQ_3:
			if( isGeneralChar( **c ) )
			{
				atrName = **c;
				seq = SEQ_4;
			}
			else if( **c == '>' )
			{
				finish = true;
			}
			break;
		case SEQ_4:
			if( isGeneralChar( **c ) )
			{
				atrName += **c;
			}
			else if( **c == '=' )
			{
				seq = SEQ_5;
			}
			break;
		case SEQ_5:
			if( **c == '"' )
			{
				seq = SEQ_6;
			}
			break;
		case SEQ_6:
			if( isGeneralChar( **c ) || **c == ' ' )
			{
				atrValue += **c;
			}
			else if( **c == '"' )
			{
				Attribute* atr = new Attribute();
				atr->setName( atrName );
				atr->setValue( atrValue );
				addAttribute( atr );
				SAFE_DELETE( atr );
				atrName.clear();
				atrValue.clear();
				seq = SEQ_3;
			}
			break;
		case SEQ_7:
			if( **c == '>' )
			{
				finish = true;
			}
			break;
		}

		if( finish )
		{
			break;
		}

		(*c)++;
	}
}

Tag::~Tag()
{
}

void Tag::addAttribute( Attribute* atr )
{
	++mAttributeSize;

	if( mAttributeSize == 1 )
	{
		mAttributes = new Attribute[mAttributeSize];
		mAttributes[0] = *atr;
		return;
	}

	Attribute* work = mAttributes;
	mAttributes = new Attribute[mAttributeSize];

	for( int i = 0; i < mAttributeSize - 1; i++ )
	{
		mAttributes[i] = work[i];
	}

	SAFE_DELETE_ARRAY( work );

	mAttributes[mAttributeSize -1] = *atr;
}

bool Tag::isGeneralChar( char c ) const
{
	const int size = 8;
	char sp[size] = { '<', ' ','=', '"', '/', '>', '\r', '\n' };

	for( int i = 0; i < size; i++ )
	{
		if( c == sp[i] )
		{
			return false;
		}
	}

	return true;
}

bool Tag::isStartTag() const
{
	return ( mType == START_TAG );
}

std::string Tag::getName() const
{
	return mName;
}

Attribute* Tag::getAttributes() const
{
	return mAttributes;
}

int Tag::getAttributeSize() const
{
	return mAttributeSize;
}
