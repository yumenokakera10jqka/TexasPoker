#pragma once
#include "Yaku.h"

class Card;

// �J�[�h�Z�b�g�����聨���ʂ̖����o���Ƃ����菇�����
class YakuHantei
{
public:
	YakuHantei(void){};
	virtual ~YakuHantei(void){};

	// ���𔻒肷��ΏۃJ�[�h���Z�b�g����
	virtual void setCards( Card** srcCards ) = 0;
	// �J�[�h�̖��𔻒肷��
	virtual bool hantei() = 0;
	// ���ƂP���Ŗ����������邩�𔻒肷��
	virtual bool hanteiRiichi()
	{
		return false;
	}
	// ���茋�ʂ�Ԃ�
	virtual const Yaku& getYaku() const = 0;
	// �����̒S���J�[�h������Ԃ�
	virtual int numInCharge() const = 0;
};
