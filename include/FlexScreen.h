#pragma once
#include <string>
#include "Format.h"
#include <map>

using namespace std;

class Col;
class Row;
class VValue;
class Element;

//��╡�G�ȕ\���R���\�[���o�͂���
//�Ⴆ�΁A�e�s�̗񐔂��قȂ�A�e�}�X�Ɏ��R�Ƀf�[�^��z�u����ꍇ
//�e�L�X�g�t�@�C������\�̍\����}�X�̖��O��ǂݎ��\���\������
//�}�X�ɕt�������O�Ń}�X���w�肵�ĕ\���l���X�V����
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
