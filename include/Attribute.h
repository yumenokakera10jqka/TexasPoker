#ifndef INCLUDE_ATTRIBUTE_H
#define INCLUDE_ATTRIBUTE_H
#include <string>

class Attribute
{
public:
	enum Type
	{
		NAME,
		ROWSIZE,
		COLSIZE,
		WIDTH,
		ALIGN,
		NONE
	};

	Attribute();
	~Attribute();

	Type getType() const;
	void setName( std::string );
	std::string getName() const;
	void setValue( std::string );
	std::string getValue() const;
	int getIntValues( int*, int ) const;
	int getUnsignedIntValues( unsigned*, int ) const;
	int getDoubleValues( double*, int ) const;
	double getDoubleValue() const;
	int getIntValue() const;
	unsigned getUnsignedValue() const;

private:
	Type mType;
	std::string mName;
	std::string mValue;
};

#endif