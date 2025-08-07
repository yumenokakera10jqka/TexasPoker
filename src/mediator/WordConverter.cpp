#include "stdafx.h"	//¦<sstream>‚Ì‘O‚Éinclude‚µ‚È‚¢‚Æ<sstream>‚ªg‚¦‚È‚¢
					// cpp‚Ìæ“ª‚ÅŒÄ‚Ño‚³‚È‚¢‚Æ‘¼‚É‚àFX‚Æ•s“s‡‚ª‹N‚±‚é
#include "WordConverter.h"
#include "Player.h"
#include "Card.h"
#include "Yaku.h"
#include <sstream>
#include <cassert>

#define CARD_CLOSE "[H]H"

#define CHOICEWORD_SIZE 9
#define TURNWORD_SIZE 6
#define WINWORD_SIZE 3
#define YAKUWORD_SIZE 11

static string gChoiceWords[] = { "‚a‚d‚s", "‚q‚`‚h‚r‚d", "‚b‚`‚k‚k", "‚b‚g‚d‚b‚j", "‚e‚n‚k‚c"
								, "‚`‚k‚k‚h‚m", "‚k‚a‚k‚h‚m‚c", "‚a‚a‚k‚h‚m‚c", "" };
static string gSuitWords[] = { "[‚c]", "[‚b]", "[‚g]", "[‚r]", "" };
static string gNumberWords[] = { "", "", "‚Q", "‚R", "‚S", "‚T", "‚U", "‚V", "‚W", "‚X"
								, "‚P‚O", "‚P‚P", "‚P‚Q", "‚P‚R", "‚`" };
static string gTurnWords[] = { "s“®’†", "", "ƒpƒX", "", "", "ƒ`ƒbƒvØ‚ê" };
static string gWinWords[] = { "‚v‚h‚mII", "‚k‚n‚r‚d", "" };
static string gYakuWords[] = { "HIGHCARD", "ONEPAIR", "TWOPAIR", "THREECARD", "STRAIGHT"
								, "FLUSH", "FULLHOUSE", "FORE CARD", "STRAIGHTFLUSH", "ROYAL", "" };

using namespace std;

WordConverter::WordConverter(void)
{
}

WordConverter::~WordConverter(void)
{
}

string WordConverter::convertChoice( Action::Choice c )
{
	assert( (int)c < CHOICEWORD_SIZE );
	return gChoiceWords[c];
}

string WordConverter::convertChoice( Player* p )
{
	return convertChoice( p->getChoice() );
}

string WordConverter::convertTurnState( Player* p )
{
	Player::TurnState ts = p->getTurnState();
	assert( (int)ts < TURNWORD_SIZE );
	return gTurnWords[ts];
}

Format::StrColor WordConverter::getTurnStateColor( Player* p )
{
	Player::TurnState ts = p->getTurnState();
	assert( (int)ts < TURNWORD_SIZE );
	switch( ts )
	{
	case Player::TURN_ACTIVE:
		return Format::COLOR_RED;
	}
	return Format::COLOR_NONE;
}

string WordConverter::convertWinState( Player* p )
{
	Player::WinState ws = p->getWinState();
	assert( (int)ws < WINWORD_SIZE );
	return gWinWords[ws];
}

string WordConverter::convertCard( const Card& c )
{
	ostringstream oss;
	
	if( c.isOpen() )
	{
		oss << gSuitWords[c.getSuit()] << gNumberWords[c.getNumber()];
	}
	else
	{
		oss << CARD_CLOSE;
	}

	return oss.str();

}

string WordConverter::toString( int iValue )
{
	ostringstream oss;
	oss << iValue;
	return oss.str();
}

string WordConverter::convertYaku( Player* p )
{
	string str = "";

	if( p->isShowDown() )
	{
		const Yaku& yaku = p->getYaku();
		Yaku::YakuSet ys = yaku.getYaku();
		assert( (int)ys < YAKUWORD_SIZE );
		str = gYakuWords[ys];
	}

	return str;
}

Format::StrColor WordConverter::getSuitColor( const Card& card )
{
	if( card.isOpen() )
	{
		switch( card.getSuit() )
		{
		case Card::SUIT_DIA:
			return Format::COLOR_YELLOW;
		case Card::SUIT_CLUB:
			return Format::COLOR_GREEN;
		case Card::SUIT_HEART:
			return Format::COLOR_PINK;
		case Card::SUIT_SPADE:
			return Format::COLOR_BLUE;
		}
	}
	return Format::COLOR_NONE;
}
