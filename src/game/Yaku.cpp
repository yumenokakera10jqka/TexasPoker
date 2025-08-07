#include "Yaku.h"
#include <cassert>
#include <string.h>

using namespace std;

Yaku::Yaku(void): mYaku( YAKU_HIGHCARD ), mYakuCards( YAKUCARD_NUM ), mNotYakuCards( CARDSET_MAX )
{
}

/*
Yaku::Yaku( const Yaku& a )
{
	*this = a;
}
*/

Yaku::~Yaku(void)
{
}

bool Yaku::operator>( const Yaku& a ) const{    
	if ( mYaku != a.mYaku ) { return mYaku > a.mYaku; }
	// ���������ꍇ
	// �����\������J�[�h�̐����Ŕ���
	for( int i = 0; i < mYakuCards.getSize(); i++ )
	{
		if( *mYakuCards[i] != *( a.mYakuCards[i] ) )
		{
			return *mYakuCards[i] > *( a.mYakuCards[i] );
		}
	}

	// �����\�����Ȃ��J�[�h�̖����͈قȂ�ꍇ������
	//��CardPack::update�őO�̃��E���h�̖��Ɣ�r����ꍇ�ɔ�������P�[�X
	// �J�[�h���r����O�ɖ������m�F����
	if( mNotYakuCards.getSize() != a.mNotYakuCards.getSize() )
	{
		return mNotYakuCards.getSize() > a.mNotYakuCards.getSize();
	}

	//�L�b�J�[�̖����𒲂ׂ�
	//�L�b�J�[�ɂ��Ă͈ȉ��̒ʂ�
	//�O��Ƃ��āA���s����͂T���̎�D��Ώۂɍs����B�|�P�b�g�ł����Ă���D�ɑI�΂�Ȃ��ꍇ������
	//�@�|�P�b�g�Q���ƃ{�[�h�T���S�Ă̂Ȃ�����ŋ��̖����\������J�[�h���I�΂�i�����y�A�Ȃ�Q���j�A
	//�A�c��i�����y�A�Ȃ�R���j���|�P�b�g�ƃ{�[�h�̎c��S�Ă̂Ȃ����狭���J�[�h�����ԂɁy�L�b�J�[�z�Ƃ��đI�΂��							
	int rest = YAKUCARD_NUM - mYakuCards.getSize();
	if( rest > mNotYakuCards.getSize() )
	{
		rest = mNotYakuCards.getSize();
	}

	// �L�b�J�[�̐����Ŕ���
	for( int i = 0; i < rest; i++ )
	{
		if( *mNotYakuCards[i] != *( a.mNotYakuCards[i] ) )
		{
			return *mNotYakuCards[i] > *( a.mNotYakuCards[i] );
		}
	}

	// �S�������Ȃ��������
	return false;
}

bool Yaku::operator<( const Yaku& a ) const{
	return a > *this;
}

bool Yaku::operator==( const Yaku& a ) const
{
	if( *this > a )
	{
		return false;
	}
	if( a > *this )
	{
		return false;
	}

	// �S�������Ȃ��������
	return true;
}

/*
Yaku& Yaku::operator=( const Yaku& a )
{
	mYaku = a.mYaku;
	mYakuCards = a.mYakuCards;
	mNotYakuCards = a.mNotYakuCards;

	memcpy_s( mYakuCards, sizeof( Card* ) * YAKUCARD_NUM
			, a.mYakuCards, sizeof( Card* ) * YAKUCARD_NUM );

	memcpy_s( mNotYakuCards, sizeof( Card* ) * CARDSET_MAX
		, a.mNotYakuCards, sizeof( Card* ) * CARDSET_MAX );

	return *this;
}
*/

void Yaku::setYaku( Yaku::YakuSet ys )
{
	mYaku = ys;
}

Yaku::YakuSet Yaku::getYaku() const
{
	return mYaku;
}

void Yaku::addYakuCard( Card* cd )
{
	mYakuCards.add( cd );
}

const Card* Yaku::getYakuCard( int pos ) const
{
	return mYakuCards[pos];
}

int Yaku::getYakuCardNum() const
{
	return mYakuCards.getSize();
}

void Yaku::addNotYakuCard( Card* cd )
{
	mNotYakuCards.add( cd );
}

const Card* Yaku::getNotYakuCard( int pos ) const
{
	return mNotYakuCards[pos];
}

int Yaku::getNotYakuCardNum() const
{
	return mNotYakuCards.getSize();
}

void Yaku::reset()
{
	mYaku = YAKU_HIGHCARD;
	mYakuCards.reset();
	mNotYakuCards.reset();
}

int Yaku::handNumInYaku() const
{
	int handNum = 0;

	for( int i = 0; i < mYakuCards.getSize(); i++ )
	{
		if( mYakuCards[i]->getPlace() == Card::PLACE_HAND )
		{
			handNum++;
		}
	}

	return handNum;
}

int Yaku::strongestCardNum( bool isYaku, bool isHand ) const
{
	int strongest = 0;
	Card::Place place = ( isHand )? Card::PLACE_HAND : Card::PLACE_TABLE;

	if( isYaku )
	{
		for( int i = 0; i < mYakuCards.getSize(); i++ )
		{
			if( mYakuCards[i]->getPlace() == place )
			{
				strongest = mYakuCards[i]->getNumber();
				break;
			}
		}
	}
	else
	{
		for( int i = 0; i < mNotYakuCards.getSize(); i++ )
		{
			if( mNotYakuCards[i]->getPlace() == place )
			{
				strongest = mNotYakuCards[i]->getNumber();
				break;
			}
		}
	}

	return strongest;
}

void Yaku::winGame()
{
	if( mYaku == YAKU_HIGHCARD )
	{
		mNotYakuCards[0]->win();
	}
	else
	{
		int size = mYakuCards.getSize();
		for( int i = 0; i < size; i++ )
		{
			mYakuCards[i]->win();
		}
	}
}
