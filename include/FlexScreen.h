#pragma once
#include <string>
#include "Format.h"
#include <map>

using namespace std;

class Col;
class Row;
class VValue;
class Element;

//やや複雑な表をコンソール出力する
//例えば、各行の列数が異なり、各マスに自由にデータを配置する場合
//テキストファイルから表の構造やマスの名前を読み取り表を構成する
//マスに付けた名前でマスを指定して表示値を更新する
class FlexScreen
{
public:

	FlexScreen( const Element* );
	~FlexScreen(void);

	void draw();
	void update( string, const VValue& );
	void update( string, const VValue&, Format::StrColor );
	void update( string, string );
	void update( string, string,  Format::StrColor );
	void clear();
	void clearRow( int );
	void clearCol( string );
	Format* getFormat( string );
	void setOneTimeColor( string, Format::StrColor );
	void addCol( string, Col* );

private:

	Row** mRows;
	int mRowNum;
	map<string, Col*> mCols;
};
