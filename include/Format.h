#pragma once
#include <windows.h>
#include <string>
#include <ios>

using namespace std;

class VValue;

class Format
{
public:
	enum Align
	{
		ALIGN_LEFT,
		ALIGN_RIGHT
	};

	enum StrColor
	{
		COLOR_RED,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_YELLOW,
		COLOR_PINK,
		COLOR_CYAN,
		COLOR_NONE
	};

	enum Decorate
	{
		DECO_SHARP,
		DECO_NONE
	};

	Format(void);
	~Format(void);

	void draw( string );
	void draw( VValue& );
	void reset();

	int mWidth;
	int mAlign;
	StrColor mOneTimeColor;
	Decorate mDeco;

private:
	void preDraw();
	void postDraw();
	void preColor();
	void postColor();

	ios::fmtflags mFlagsSaved;
	HANDLE mHConsole;
};
