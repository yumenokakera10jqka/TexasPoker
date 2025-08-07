#pragma once
#include <string>
#include "Format.h"

using namespace std;

class VValue
{
public:
	VValue(void);
	~VValue(void);

	void setValue( string );
	void setColor( Format::StrColor );
	string getValue() const;
	Format::StrColor getColor() const;
	void clear();
	Format* getFormat();
	void draw();

private:
	string mValue;
	Format mFormat;
};
