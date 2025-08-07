#pragma once

class Col;
class Element;
class FlexScreen;

class Row
{
public:
	Row( const Element*, FlexScreen* );
	Row( int );
	~Row(void);

	void draw();
	void addCol( Col*, int );
	void clear();

	Col* operator[]( int );

private:
	Col** mCols;
	int mColNum;
};
