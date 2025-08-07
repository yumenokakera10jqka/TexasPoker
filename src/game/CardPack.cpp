#include "CardPack.h"
#include "TableCard.h"
#include "Card.h"
#include "YakuHantei.h"
#include <cassert>

using namespace std;

CardPack::CardPack( TableCard* tc ): mTable( tc ), mHandNum( 0 )
{
}

CardPack::~CardPack(void)
{
	//TODO:TEST
	/*
	map<int, YakuHantei*>::iterator it;
	for( it = mYakuHantei.begin() ; it != mYakuHantei.end(); it++ ){
		delete( (*it).second );
		(*it).second = 0;
	}
	*/
}

void CardPack::addYakuHantei( YakuHantei* yakuHantei )
{
	// �S���J�[�h�����𕷂��ăL�[�Ƃ���
	mYakuHantei[yakuHantei->numInCharge()] = yakuHantei;
}

void CardPack::setHand( Card* card )
{
	assert( 0 <= mHandNum && mHandNum < HANDCARD_MAX );

	card->setPlace( Card::PLACE_HAND );	//TODO:�e�X�g
	mHands[mHandNum++] = card;
}

const Card& CardPack::getHand( int pos ) const
{
	assert( 0 <= pos && pos < mHandNum );

	return *mHands[pos];
}

int CardPack::getHandNum() const
{
	return mHandNum;
}

int CardPack::getTableCardNum() const
{
	return mTable->getCardNum();
}

const Yaku& CardPack::getYaku() const
{
	return mYaku;
}

CardSetIterator CardPack::createIterator()
{
	assert( mHandNum == HANDCARD_MAX && mTable->getCardNum() >= TABLECARD_MINNUM );

	CardSetIterator cIterator( YAKUCARD_NUM );

	// �C�e���[�^�Ɍ��݂̑S�Ẵn���h�J�[�h���Z�b�g
	for( int i = 0; i < HANDCARD_MAX; i++ )
	{
		cIterator.setCard( mHands[i] );
	}

	Card* tableCards[TABLECARD_MAX];
	int tableCardNum = mTable->getCardNum();
	mTable->getCards( tableCards, tableCardNum );

	// �C�e���[�^�Ɍ��݂̑S�Ẵe�[�u���J�[�h���Z�b�g
	for( int i = 0; i < tableCardNum; i++ )
	{
		cIterator.setCard( tableCards[i] );
	}

	return cIterator;
}

void CardPack::updateYaku()
{
	// �n���h�J�[�h���Z�b�g����Ă��Ȃ��ꍇ
	if( mHandNum < HANDCARD_MAX )
	{
		return;
	}

	YakuHantei* yakuHantei = 0;

	// �n���h�J�[�h���Z�b�g����Ă��邪�e�[�u���J�[�h���Z�b�g����Ă��Ȃ��ꍇ
	if( mHandNum == HANDCARD_MAX 
		&& mTable->getCardNum() < TABLECARD_MINNUM )
	{
		// �𔻒�I�u�W�F�N�g�̎擾
		assert( mYakuHantei.count( mHandNum ) );
		yakuHantei = mYakuHantei[mHandNum];
		// �n���h�J�[�h�݂̂Ŗ��X�V������
		yakuHantei->setCards( mHands );
		yakuHantei->hantei();
		mYaku = yakuHantei->getYaku();

		return;
	}

	// �n���h�J�[�h�ƃe�[�u���J�[�h�����v�T���ȏ゠��ꍇ
	CardSetIterator cIterator = createIterator();
	int cardNum = cIterator.getCardNum();	// �n���h�ƃe�[�u���̍��v�J�[�h����
	int selectNum = cIterator.getSelectNum();	// ����Ώۂ̃J�[�h����
	Card** cardPtrs = 0;
	Yaku yakuTmp;	// ���茋�ʂ��ꎞ�I�Ɋi�[
	Yaku yakuStrongest;
	yakuStrongest = mYaku;	// �ł����������i�[
	// �𔻒�I�u�W�F�N�g�̎擾
	assert( mYakuHantei.count( selectNum ) );
	yakuHantei = mYakuHantei[selectNum];

	while( ( cardPtrs = cIterator.getNextSet() ) != 0 )
	{
		yakuHantei->setCards( cardPtrs );
		yakuHantei->hantei();
		yakuTmp = yakuHantei->getYaku();
		for( int i = selectNum; i < cardNum; i++ )
		{
			yakuTmp.addNotYakuCard( cardPtrs[i] );
		}
		if( yakuTmp > yakuStrongest )
		{
			yakuStrongest = yakuTmp;
		}
	}

	if( yakuStrongest > mYaku )
	{
		mYaku = yakuStrongest;
	}
}

void CardPack::reset()
{
	for( int i = 0; i < HANDCARD_MAX; i++)
	{
		mHands[i] = 0;
	}
	mHandNum = 0;
}

void CardPack::openHand()
{
	for( int i = 0; i < mHandNum; i++)
	{
		mHands[i]->open();
	}
}

void CardPack::winGame()
{
	mYaku.winGame();
}
