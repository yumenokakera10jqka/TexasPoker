#pragma once
#include <map>

using namespace std;

class ScreenOperator;

class View
{
public:
	enum ViewState
	{
		VST_CARDTOPLAYER,
		VST_CARDTOTABLE,
		VST_PLAYERINPUT,
		VST_PLAYERDECISION,
		VST_CPUDECISION,
		VST_SHOWDOWN,
		VST_FINISHGAME,
		VST_NONE,
		VST_SIZE
	};

	enum ScreenName
	{
		SCREEN_RIVALS,
		SCREEN_PLAYER,
		SCREEN_TABLE,
		SCREEN_RESULT
	};

	View();
	~View(void);

	void draw( ViewState );
	void drawResult();
	void drawGameStart();
	void drawRoundStart();

private:
	void createScreen();
	void fixConsoleSize();

	map<ScreenName, ScreenOperator*> mScreens;
};