#pragma once
#include <string>
#include "Format.h"

using namespace std;

class Row;
class VValue;

//�P���ȕ\���R���\�[���o�͂���
//�Ⴆ�΁A�e�s�̗񐔂��S�ē����ŁA�e�}�X�ɋK���I�Ƀf�[�^��z�u����ꍇ
//�s�Ɨ�̃C���f�b�N�X�Ń}�X���w�肵�ĕ\���l���X�V����
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
