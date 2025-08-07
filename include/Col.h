#pragma once
#include <string>
#include "Format.h"
#include "VValue.h"

class Element;
class FlexScreen;

using namespace std;

class Col
{
public:
	Col( const Element*, FlexScreen* );
	Col();
	~Col(void);

	void setValue( const VValue& );
	void setValue( string );
	void draw();

	void setFormat( Format );
	Format* getFormat();
	int getWidth() const;
	void clear();

private:
	string mName;
	Format mFormat;
	VValue mVValue;
};
