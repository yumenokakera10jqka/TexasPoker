#pragma once

#define CARD_SUITNUM 4
#define CARD_LOWNUMBER 2
#define CARD_HIGHNUMBER 14

class Card
{
public:
	Card(void);
	~Card(void);

	enum Suit
	{
		SUIT_DIA,
		SUIT_CLUB,
		SUIT_HEART,
		SUIT_SPADE,
		SUIT_NONE
	};

	enum Place
	{
		PLACE_HAND,
		PLACE_TABLE,
		PLACE_DECK
	};

	int getNumber() const;
	void setNumber( int );
	Suit getSuit() const;
	void setSuit( Suit );
	void reset();
	void win();
	bool isWin() const;
	Place getPlace() const;
	void setPlace( Place );
	void open();
	void close();
	bool isOpen() const;

	// �J�[�h�̋��㔻��֐�
	bool operator>( const Card& ) const;
	bool operator<( const Card& ) const;
	bool operator==( const Card& ) const;
	bool operator!=( const Card& ) const;

private:
	int mNumber;
	Suit mSuit;
	bool mIsWin;	// �����J�[�h�t���O
	Place mPlace;
	bool mOpen;
};
