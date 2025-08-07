#ifndef INCLUDE_ELEMENT_H
#define INCLUDE_ELEMENT_H
#include <string>
#include "Attribute.h"

class Tag;

class Element
{
public:
	enum Type
	{
		SCREEN,
		ROW,
		COL,
		NONE,
	};

	Element();
	Element( const Tag&, const char** );
	~Element();

	void setType( Type );
	Type getType() const;
	void setName( std::string );
	std::string getName() const;
	void setAttributeSize( int );
	int getAttributeSize() const;
	void setAttributes( Attribute* );
	const Attribute* getAttributes() const;
	const Attribute* getAttribute( Attribute::Type ) const;
	void setChildSize( int );
	int getChildSize() const;
	void setChilds( Element* );
	Element* getChilds() const;
	void copy( const Element& );
	const Element* getChild( int ) const;
	const Attribute* getAttribute( int ) const;

private:
	Type mType;
	std::string mName;
	Attribute* mAttributes;
	int mAttributeSize;
	Element* mChilds;
	int mChildSize;

	void addElement( Element* );
};

#endif