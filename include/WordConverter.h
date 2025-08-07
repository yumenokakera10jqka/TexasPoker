#pragma once
#include <string>
#include "Action.h"
#include "Format.h"

using namespace std;

class Player;
class Card;

class WordConverter
{
public:
	WordConverter(void);
	~WordConverter(void);

	static string convertChoice( Action::Choice );
	static string convertChoice( Player* );
	static string convertTurnState( Player* );
	static Format::StrColor getTurnStateColor( Player* );
	static string convertWinState( Player* );
	static string toString( int );
	static string convertYaku( Player* );
	static string convertCard( const Card& );
	static Format::StrColor getSuitColor( const Card& );
};
