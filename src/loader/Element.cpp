#include "Element.h"
#include "MyMacro.h"
#include "Attribute.h"
#include "Tag.h"

Element::Element( const Tag& tag, const char** c ):
mType( NONE ), mName( "" ), mAttributes( 0 ), mAttributeSize( 0 ), mChilds( 0 ), mChildSize( 0 )
{
	setName( tag.getName() );
	mAttributes = tag.getAttributes();
	mAttributeSize = tag.getAttributeSize();

	while( **c != '\0' )
	{
		if( **c == '<' )
		{
			Tag* tmp = new Tag( c );

			if( tmp->isStartTag() )
			{
				Element* e = new Element( *tmp, c );
				SAFE_DELETE( tmp );
				addElement( e );
				SAFE_DELETE( e );
			}
			else
			{
				SAFE_DELETE( tmp );
				break;
			}
		}

		++(*c);
	}
}

Element::Element()
{
}

Element::~Element()
{
	if( mAttributeSize > 0 )
	{
		if( mAttributes != 0 )
		{
			SAFE_DELETE_ARRAY( mAttributes );
		}
	}
	if( mChildSize > 0 )
	{
		if( mChilds != 0 )
		{
			SAFE_DELETE_ARRAY( mChilds );
		}
	}
}

void Element::addElement( Element* e )
{
	++mChildSize;

	if( mChildSize == 1 )
	{
		mChilds = new Element[mChildSize];
		mChilds[0].copy( *e );
		return;
	}

	Element* work = mChilds;
	mChilds = new Element[mChildSize];

	for( int i = 0; i < mChildSize - 1; i++ )
	{
		mChilds[i].copy( work[i] );
	}

	SAFE_DELETE_ARRAY( work );

	mChilds[mChildSize-1].copy( *e );
}

void Element::copy( const Element& e )
{
	mType = e.mType;
	mName = e.mName;
	mAttributeSize = e.mAttributeSize;
	mChildSize = e.mChildSize;

	mAttributes = new Attribute[mAttributeSize];
	for( int i = 0; i < mAttributeSize; i++ )
	{
		mAttributes[i] = e.getAttributes()[i];
	}

	mChilds = new Element[mChildSize];
	for( int i = 0; i < mChildSize; i++ )
	{
		mChilds[i].copy( e.getChilds()[i] );
	}
}


void Element::setType( Type type )
{
	mType = type;
}

Element::Type Element::getType() const
{
	return mType;
}

void Element::setName( std::string name )
{
	mName = name;

	if( name == "screen" )
	{
		mType = SCREEN;
	}
	else if( name == "row" )
	{
		mType = ROW;
	}
	else if( name == "col" )
	{
		mType = COL;
	}
	else
	{
		mType = NONE;
	}

}

std::string Element::getName() const
{
	return mName;
}

void Element::setAttributeSize( int size )
{
	mAttributeSize = size;
}

int Element::getAttributeSize() const
{
	return mAttributeSize;
}

void Element::setAttributes( Attribute* attributes )
{
	mAttributes = attributes;
}

const Attribute* Element::getAttributes() const
{
	return mAttributes;
}

const Attribute* Element::getAttribute( Attribute::Type type ) const
{
	for( int i = 0; i < mAttributeSize; i++ )
	{
		if( mAttributes[i].getType() == type  )
		{
			return &mAttributes[i];
		}
	}

	return 0;
}

void Element::setChildSize( int size )
{
	mChildSize = size;
}

int Element::getChildSize() const
{
	return mChildSize;
}

void Element::setChilds( Element* childs )
{
	mChilds = childs;
}

Element* Element::getChilds() const
{
	return mChilds;
}

const Element* Element::getChild( int i ) const
{
	if( i > mChildSize - 1 )
	{
		return 0;
	}
	return &mChilds[i];
}

const Attribute* Element::getAttribute( int i ) const
{
	if( i > mAttributeSize - 1 )
	{
		return 0;
	}
	return &mAttributes[i];

}
