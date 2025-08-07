#pragma once
#include <string>
#include "Format.h"

using namespace std;

class Row;
class VValue;

//単純な表をコンソール出力する
//例えば、各行の列数が全て同じで、各マスに規則的にデータを配置する場合
//行と列のインデックスでマスを指定して表示値を更新する
class Screen
{
public:

	Screen( int, int );
	~Screen(void);

	void draw();
	void update( int, int, const VValue& );
	void update( int, int, string );
	void clearRow( int );
	void clearCol( int );
	Format* getFormat( int, int );
	void setOneTimeColor( int, int, Format::StrColor );

private:
	void addCol( int, int );

	Row** mRows;
	int mRowNum;
	int mColNum;

};
